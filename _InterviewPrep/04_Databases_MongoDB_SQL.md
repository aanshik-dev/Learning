# Domain 04: Databases (MongoDB, Relational SQL & Data Modeling)

This guide covers database architecture, indexing, concurrency control, ACID transactions, and schema design comparing **MongoDB (NoSQL Document Store)** with **Relational Databases (MySQL / SQLite / PostgreSQL)** based on your project and internship experience.

---

## 1. Relational (SQL) vs. Document (MongoDB) Architecture

| Feature | Relational Databases (MySQL, PostgreSQL, SQLite) | MongoDB (Document NoSQL) |
| :--- | :--- | :--- |
| **Data Model** | Rigid tables, rows, foreign key constraints | Flexible BSON (Binary JSON) documents |
| **Schema** | Static schema (DDL migrations required) | Dynamic / Schema-on-read (enforced via Mongoose) |
| **Relationships** | Joins (`INNER JOIN`, `LEFT JOIN`) | Embedded documents or Document references (`$lookup`) |
| **Scaling** | Vertical scaling primarily; horizontal via read-replicas & sharding | Native horizontal sharding via partition keys |
| **ACID Support** | Native, granular multi-row ACID across all tables | Full ACID support for multi-document transactions (since MongoDB 4.0) |

---

## 2. MongoDB Deep Dive & Production Modeling

### 2.1 Embedding vs. Referencing (Data Modeling Rules)
- **Rule of Thumb:**
  - *Embed* if: "Contains" relationship, $1:1$ or $1:N$ where $N$ is small and bounded ($<100$), and data is almost always read together (e.g., Address inside a Farmer Profile, or Items inside a specific Pickup batch).
  - *Reference* if: $1:N$ where $N$ is unbounded (e.g., thousands of Deal Logs, User Transactions), or many-to-many ($N:M$) relationships (e.g., Farmers to Collectives). Avoid the 16MB BSON document limit!

### 2.2 Normalized Schemas & Multi-Document Transactions in MongoDB
In your internship and *FarmFresh*, you architected transactional workflows for crop listings, deal requests, and pickup scheduling without data conflicts.

```javascript
import mongoose from 'mongoose';

// Reserving crop inventory and scheduling pickup atomically using MongoDB Transactions:
export async function schedulePickupWithTransaction({ listingId, buyerId, quantityKg, scheduledDate }) {
  const session = await mongoose.startSession();
  session.startTransaction();

  try {
    // 1. Find and atomically check/decrement available inventory
    const listing = await mongoose.model('CropListing').findOneAndUpdate(
      {
        _id: listingId,
        availableQuantity: { $gte: quantityKg }, // Concurrency guard: prevents overselling
        status: 'ACTIVE'
      },
      {
        $inc: { availableQuantity: -quantityKg }
      },
      { new: true, session }
    );

    if (!listing) {
      throw new Error('Insufficient inventory or listing no longer active');
    }

    // 2. Create the pickup schedule record
    const pickupSchedule = await mongoose.model('PickupSchedule').create(
      [
        {
          listing: listingId,
          buyer: buyerId,
          quantityKg,
          scheduledDate,
          status: 'PENDING_DRIVER'
        }
      ],
      { session }
    );

    // 3. Commit transaction
    await session.commitTransaction();
    return pickupSchedule[0];
  } catch (error) {
    // Abort transaction on any failure (rolls back inventory decrement)
    await session.abortTransaction();
    throw error;
  } finally {
    session.endSession();
  }
}
```

### 2.3 MongoDB Aggregation Framework
Used for real-time reporting, analytics, and complex joins:

```javascript
// Example: Grouping pickup metrics by Zone in FarmFresh
const zoneMetrics = await PickupSchedule.aggregate([
  { $match: { status: 'COMPLETED' } },
  {
    $group: {
      _id: '$zoneId',
      totalDeliveries: { $sum: 1 },
      totalWeightKg: { $sum: '$quantityKg' },
      avgCompletionTimeMinutes: { $avg: '$completionDuration' }
    }
  },
  { $sort: { totalWeightKg: -1 } }
]);
```

### 2.4 Indexing in MongoDB
- **Default Index:** `_id` (unique B-tree index).
- **Compound Indexes:** Order matters! Follow the **ESR Rule (Equality, Sort, Range)**.
  - Example: `db.crops.createIndex({ status: 1, region: 1, pricePerKg: 1 })`
  - Query: `find({ status: "ACTIVE", region: "Himalayan" }).sort({ pricePerKg: 1 })` uses the index efficiently for both filtering and sorting without an in-memory sort stage.
- **Unique Indexes:** Enforces constraints (e.g., `{ utrNumber: 1 }, { unique: true }` for immutable payment records in FarmFresh).

---

## 3. Relational SQL & SQLite (Insight Forge Context)

### 3.1 ACID Properties Explained
1. **Atomicity:** All operations in a transaction succeed, or the entire transaction is rolled back.
2. **Consistency:** Database transitions from one valid state to another, obeying all constraints (foreign keys, uniqueness, checks).
3. **Isolation:** Concurrent transactions execute without interfering with one another.
4. **Durability:** Once committed, data persists even in the event of a crash (Write-Ahead Logging / WAL).

### 3.2 SQL Transaction Isolation Levels & Concurrency Phenomena
| Isolation Level | Dirty Read | Non-Repeatable Read | Phantom Read |
| :--- | :---: | :---: | :---: |
| **Read Uncommitted** | Yes | Yes | Yes |
| **Read Committed** | No | Yes | Yes |
| **Repeatable Read** (MySQL default) | No | No | Yes (mitigated via Next-Key locks in InnoDB) |
| **Serializable** (Highest safety) | No | No | No |

- **Dirty Read:** Reading uncommitted changes made by another active transaction that may later rollback.
- **Non-Repeatable Read:** Re-reading the same row within a transaction returns different data because another transaction modified and committed it.
- **Phantom Read:** Re-executing a range query returns newly inserted rows committed by another transaction.

---

### 3.3 Database Normalization
- **1NF (First Normal Form):** Atomic values (no repeating groups or arrays in columns), each row has a primary key.
- **2NF (Second Normal Form):** Must be in 1NF and have **no partial dependencies** (every non-key attribute must depend on the *whole* primary key, relevant for composite keys).
- **3NF (Third Normal Form):** Must be in 2NF and have **no transitive dependencies** (non-key attributes must not depend on other non-key attributes: $X \to Y \to Z$).
- **BCNF (Boyce-Codd Normal Form):** A stricter version of 3NF where for every functional dependency $X \to Y$, $X$ must be a super key.

---

### 3.4 B-Tree Index Mechanics
- Relational databases utilize balanced search trees (B-Trees / B+ Trees) for indexing.
- Search, insertion, and deletion complexity: $O(\log N)$.
- B+ Trees store all actual record pointers in leaf nodes linked as a doubly linked list, making **range queries (`BETWEEN`, `>`, `<`)** extremely fast.
- **When NOT to index:**
  - High-write, low-read tables (every `INSERT`/`UPDATE` incurs index tree rebalancing overhead).
  - Low cardinality columns (e.g., Boolean `is_active` or Gender with only 2 values)—the query optimizer will usually bypass the index and perform a full table scan.
