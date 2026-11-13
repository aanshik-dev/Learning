<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **CLOUD COMPUTING - FORMAL EXAM ANSWERS** 🔥🐦‍🔥

> Academic Examination Solutions: Mid Semester Previous Year Papers (2024 & 2025)
> Plus 25 High-Yield Comprehensive Examination Questions & Model Answers
> Course: CS351 Cloud Computing | Department of Computer Science & Engineering

<br>

---

# 🐦‍🔥 MID SEMESTER EXAMINATION 2024

---

<br>

## 🔥 Q1(a) [2 marks] In cloud computing, multiple customers can share a cloud resource while maintaining data isolation. Justify how.

**Answer:**

Cloud service providers achieve multi-tenant resource sharing with complete data isolation through virtualization and logical isolation mechanisms:

1. **Hypervisor-Level Isolation:** A hypervisor (Virtual Machine Monitor) enforces hardware-level boundary isolation between Virtual Machines (VMs) co-located on the same physical host. Each VM operates within an isolated memory space, isolated CPU registers, and separate virtual hardware namespaces.
2. **Virtual Network Separation:** Cloud platforms utilize software-defined virtual private networks (e.g., AWS VPC) using encapsulation protocols such as VXLAN and VLAN tags. Network traffic between tenants is cryptographically and logically segregated using Virtual Routing and Forwarding (VRF) and stateful security group firewalls.
3. **Storage and Namespace Partitioning:** At the storage layer, block devices (e.g., AWS EBS) and object stores (e.g., AWS S3) enforce logical partitioning using unique tenant identifiers, cryptographic access controls, and automated block wiping prior to reallocation.
4. **Identity and Access Management (IAM) & Role-Based Access Control (RBAC):** Each customer operates within a distinct account boundary. IAM policies explicitly enforce least-privilege access, ensuring cross-tenant resource inspection or unauthorized API calls are strictly denied.
5. **Data Encryption with Customer Managed Keys:** Data at rest and data in transit are encrypted using tenant-specific cryptographic keys managed by Hardware Security Modules (AWS KMS / CloudHSM). Even if underlying physical storage media is shared, ciphertext cannot be decrypted across tenant boundaries.

<br>

## 🔥 Q1(b) [3 marks] Suppose a cloud-based application is experiencing a spike in traffic. Explain how cloud computing can handle this situation.

**Answer:**

Cloud computing handles sudden traffic surges seamlessly through dynamic resource elasticity, automated horizontal scaling, and traffic distribution mechanisms:

1. **Metric Telemetry & Monitoring:** Continuous monitoring systems (e.g., Amazon CloudWatch) collect operational telemetry such as CPU Utilization, Memory Pressure, Network I/O, and Application Load Balancer Request Count per Target at periodic intervals (e.g., 60 seconds).
2. **Dynamic Horizontal Auto Scaling (Scale-Out):**
   - When incoming traffic drives a key metric beyond a predefined threshold (e.g., Average CPU Utilization $> 75\%$), a CloudWatch Alarm transitions to the `ALARM` state.
   - The alarm triggers a scale-out policy associated with the Auto Scaling Group (ASG).
   - The ASG launches additional virtual machine instances based on a predefined Launch Template/Configuration until the desired capacity meets the workload requirement (up to `MaxSize`).
3. **Elastic Load Balancing (ELB):**
   - An Elastic Load Balancer receives incoming client requests at a single entry point and distributes them across all healthy registered EC2 instances using algorithms like Round Robin or Least Outstanding Requests.
   - As new instances are initialized and pass health checks, the ELB automatically registers them into the active target group.
4. **Elastic Data & Caching Tier Offloading:**
   - Content Delivery Networks (e.g., Amazon CloudFront) cache static assets at edge locations close to end-users, absorbing up to 80% of traffic before reaching the origin.
   - Distributed in-memory caches (e.g., Redis/Memcached) mitigate database read bottlenecks.
5. **Automated Scale-In (Resource Release):**
   - Once the surge subsides and metrics drop below low-watermark thresholds (e.g., CPU $< 30\%$), scale-in policies safely deregister and terminate surplus instances, returning to baseline capacity and minimizing operational cost.

<br>

## 🔥 Q2(a) [2 marks] Differentiate between a type-1 hypervisor and a type-2 hypervisor.

**Answer:**

| Parameter | Type-1 Hypervisor (Bare-Metal) | Type-2 Hypervisor (Hosted) |
| :--- | :--- | :--- |
| **Execution Layer** | Runs directly on bare physical server hardware. | Runs on top of an existing Host Operating System. |
| **Architectural Stack** | `Hardware` $\rightarrow$ `Hypervisor` $\rightarrow$ `Guest VMs` | `Hardware` $\rightarrow$ `Host OS` $\rightarrow$ `Hypervisor` $\rightarrow$ `Guest VMs` |
| **Performance** | High throughput and near-native execution speed; no intermediate host OS latency. | Slower execution speed; context switching and host OS syscall overhead reduce I/O throughput. |
| **Resource Overhead** | Very low footprint; hypervisor is streamlined solely for virtualization. | High overhead; consumes host OS memory, CPU scheduling, and background services. |
| **Security Surface** | Highly secure; minimal codebase and tiny attack surface. | Less secure; any compromise of the underlying host OS compromises all guest VMs. |
| **Primary Use Cases** | Enterprise data centers, public cloud infrastructures (AWS, GCP, Azure). | Software development, personal desktop virtualization, local testing environments. |
| **Industry Examples** | VMware ESXi, Citrix XenServer, KVM, Microsoft Hyper-V. | Oracle VirtualBox, VMware Workstation, VMware Fusion, Parallels. |

```
Type-1 (Bare-Metal):              Type-2 (Hosted):
+-----------------------+         +-----------------------+
|  VM 1   |    VM 2     |         |  VM 1   |    VM 2     |
| (Guest) |   (Guest)   |         | (Guest) |   (Guest)   |
+-----------------------+         +-----------------------+
|   Type-1 Hypervisor   |         |   Type-2 Hypervisor   |
+-----------------------+         +-----------------------+
|   Physical Hardware   |         |  Host Operating System|
+-----------------------+         +-----------------------+
                                  |   Physical Hardware   |
                                  +-----------------------+
```

<br>

## 🔥 Q2(b) [3 marks] Does the guest operating system need to be modified to run in a virtual machine? Justify.

**Answer:**

Whether a guest operating system requires kernel modification depends strictly on the underlying virtualization architecture:

1. **Full Virtualization (No Modification Required):**
   - The hypervisor provides complete architectural simulation of underlying physical hardware.
   - The guest OS is entirely unaware that it is running in a virtual environment and requires **zero kernel modifications**.
   - Privileged and sensitive non-virtualizable x86 instructions are intercepted and handled via runtime binary translation.
   - *Examples:* VMware Workstation, early VirtualBox.
2. **Hardware-Assisted Virtualization (No Modification Required):**
   - Modern microprocessors incorporate dedicated silicon virtualization extensions (Intel VT-x with VMX root/non-root modes, AMD-V).
   - Sensitive instructions executed by the unmodified guest OS automatically trap directly into the hypervisor without software emulation or binary translation.
   - The guest OS runs completely **unmodified** with near-native performance.
   - *Examples:* KVM, VMware ESXi, AWS Nitro Hypervisor.
3. **Para-Virtualization (Kernel Modification Required):**
   - The guest operating system **must be modified** prior to execution.
   - The guest OS kernel is made explicitly aware that it is executing inside a virtual machine.
   - Non-virtualizable sensitive hardware instructions are stripped out and replaced with software routines known as **Hypercalls** (analogous to system calls directly into the hypervisor).
   - *Benefit:* Eliminates binary translation overhead, offering high I/O throughput.
   - *Example:* Original Xen para-virtualized guests (PV-Linux).

**Conclusion:** Modification is **not required** for Full Virtualization and Hardware-Assisted Virtualization, whereas it is **mandatory** for Para-Virtualization.

<br>

## 🔥 Q3(a) [2 marks] Can a load balancer ensure high availability in cloud computing? Explain.

**Answer:**

**Yes, a load balancer is a foundational mechanism for achieving High Availability (HA) in cloud architectures.** It guarantees HA through the following mechanisms:

1. **Active Fault Detection (Health Checks):**
   - The load balancer periodically executes synthetic health check probes (HTTP/HTTPS GET requests or TCP handshakes) against registered backend instances.
   - If an instance fails to respond with a healthy HTTP status code (e.g., 200 OK) within a defined timeout period, the load balancer marks it as `unhealthy` and immediately stops routing traffic to it.
2. **Dynamic Traffic Rerouting:**
   - Traffic is seamlessly rerouted exclusively to remaining healthy compute instances without user interruption or dropped requests.
3. **Multi-Availability Zone (Multi-AZ) Redundancy:**
   - Load balancers (e.g., AWS Application Load Balancer) can distribute incoming requests across redundant target instances deployed across geographically distinct availability zones.
   - If an entire availability zone suffers a catastrophic facility outage (power, network, fire), the load balancer routes all incoming requests to operational zones.
4. **Zero-Downtime Maintenance & Rolling Upgrades:**
   - Instances can be drained of connections, updated, and re-registered sequentially without taking the overall service offline.

<br>

## 🔥 Q3(b) [3 marks] Monitoring in cloud computing can help to ensure that the service level agreement is met. Justify how.

**Answer:**

A Service Level Agreement (SLA) is a legally binding commitment between a cloud service provider and consumer specifying quantitative Service Level Objectives (SLOs) such as uptime percentage (e.g., 99.99%), maximum response latency, and throughput guarantees.

Monitoring ensures SLA compliance through:

1. **Continuous Telemetry Tracking Against SLO Targets:**
   - Monitoring systems (e.g., Amazon CloudWatch, Datadog) track real-time operational metrics across compute, network, and application layers (e.g., Request Latency, 5xx Error Rates, Uptime Availability).
   - This metric stream provides continuous verification against contracted SLO targets.
2. **Proactive Anomaly Detection & Early Warning Alerts:**
   - Alarms trigger threshold notifications (e.g., average HTTP latency exceeding 250 ms for two consecutive evaluation periods) *before* an SLA breach occurs.
   - Operators can rectify database deadlocks, memory leaks, or network saturation before downtime thresholds are violated.
3. **Automated Elastic Remediation:**
   - Telemetry directly drives automated remediation scripts and auto-scaling policies. If compute demand spikes threaten response time commitments, additional capacity is provisioned autonomously.
4. **Historical SLA Compliance Auditing and Dispute Verification:**
   - Monitoring services maintain tamper-proof, timestamped operational logs and uptime records.
   - These records serve as legal audit evidence to calculate service credits or contractual penalty compensation when an SLA violation takes place.

<br>

## 🔥 Q4(a) [2 marks] Write about two benefits of MapReduce in cloud computing.

**Answer:**

1. **Massive Parallelism with Data Locality:**
   - MapReduce partitions massive datasets across distributed storage blocks (e.g., HDFS, S3) and processes them concurrently across hundreds or thousands of commodity compute nodes.
   - It adheres to the principle of **Data Locality** (moving computation tasks to the physical nodes where data resides, rather than transferring terabytes of raw data across network switches), drastically minimizing network I/O bottlenecks.
2. **Inherent Fault Tolerance & Elastic Cloud Integration:**
   - If a worker node crashes during execution, the master/resource manager detects heartbeat failure and autonomously re-assigns incomplete Map or Reduce tasks to alternative healthy nodes without restarting the overall batch job.
   - In cloud environments (e.g., Amazon EMR), MapReduce clusters can dynamically scale their compute nodes up or down on demand, capitalizing on cost-effective spot instances.

<br>

## 🔥 Q4(b) [2 marks] What are the functions of policies in identity and access management?

**Answer:**

In Identity and Access Management (IAM), a policy is a formal JSON document that defines authorization permissions. Its primary functions include:

1. **Granular Access Control:** Explicitly defines which actions (`Action`, e.g., `s3:GetObject`, `ec2:RunInstances`) are permitted or forbidden (`Effect: Allow` or `Effect: Deny`) on specific resources (`Resource`, e.g., `arn:aws:s3:::my-bucket/*`).
2. **Enforcement of the Principle of Least Privilege:** Restricts users, groups, and service roles to only the minimum privileges required to execute their specific operational duties.
3. **Contextual & Conditional Access Governance:** Imposes conditional rules (`Condition`) based on environment factors such as client source IP range (`aws:SourceIp`), multi-factor authentication status (`aws:MultiFactorAuthPresent`), and temporal boundaries (valid time windows).
4. **Permission Boundary Definition:** Establishes the maximum allowable permissions an entity can possess, preventing privilege escalation by delegated administrators.

<br>

## 🔥 Q4(c) [2 marks] How does the OpenFlow protocol help in software defined networking?

**Answer:**

OpenFlow is the industry-standard **Southbound Interface** protocol in Software Defined Networking (SDN) that enables programmable control of network forwarding hardware:

1. **Decoupling Control Plane from Data Plane:** OpenFlow provides an open, vendor-agnostic communication channel between the centralized SDN Controller (control plane) and underlying physical or virtual network switches (data plane).
2. **Flow Table Manipulation:** Enables the SDN Controller to dynamically insert, inspect, modify, and remove packet-forwarding entries inside the switch's hardware **Flow Tables**.
3. **Programmable Packet Handling:** Instead of static routing protocols, switches perform packet matching (based on IP headers, MAC addresses, TCP ports) and execute controller-directed actions: `Forward`, `Drop`, `Modify Header`, or `Send to Controller`.
4. **Dynamic Network Optimization:** Facilitates real-time traffic engineering, adaptive load balancing, and dynamic quality-of-service (QoS) adjustments without requiring individual hardware switch reconfigurations.

<br>

## 🔥 Q5 Write the boto command to:

### (a) Launch an EC2 instance [1 mark]
```python
import boto3

ec2 = boto3.client('ec2', region_name='ap-south-1')
response = ec2.run_instances(
    ImageId='ami-0abcdef1234567890',
    InstanceType='t2.micro',
    MinCount=1,
    MaxCount=1,
    KeyName='my-key-pair'
)
```

### (b) Upload a file to S3 bucket [1 mark]
```python
import boto3

s3 = boto3.client('s3')
s3.upload_file(
    Filename='local_file.txt',
    Bucket='my-cloud-bucket',
    Key='documents/remote_file.txt'
)
```

### (c) Get IP address of Amazon EC2 instance [1 mark]
```python
import boto3

ec2 = boto3.client('ec2', region_name='ap-south-1')
response = ec2.describe_instances(InstanceIds=['i-0123456789abcdef0'])
public_ip = response['Reservations'][0]['Instances'][0].get('PublicIpAddress')
print("Public IP Address:", public_ip)
```

### (d) List running Amazon EC2 instances [1 mark]
```python
import boto3

ec2 = boto3.client('ec2', region_name='ap-south-1')
response = ec2.describe_instances(
    Filters=[{'Name': 'instance-state-name', 'Values': ['running']}]
)

for reservation in response['Reservations']:
    for instance in reservation['Instances']:
        print(f"Running Instance ID: {instance['InstanceId']}, Type: {instance['InstanceType']}")
```

<br>

## 🔥 Q6(a) [2 marks] What are the functions of publishers and subscribers in Amazon SNS?

**Answer:**

Amazon Simple Notification Service (SNS) operates on a decoupled publish-subscribe (Pub/Sub) messaging paradigm:

1. **Publishers:**
   - Act as asynchronous message producers.
   - Generate payload messages and publish them to a logical access point called an **SNS Topic**.
   - Operates completely decoupled from consumers; publishers possess no knowledge of recipient identities, network addresses, or transport protocols.
   - *Example:* An e-commerce billing service publishing an `OrderPlaced` event to a topic.
2. **Subscribers:**
   - Act as message consumers that register endpoints to listen for notifications emitted by specific topics.
   - Receive broadcast fan-out deliveries over diverse supported communication protocols: Amazon SQS queues, AWS Lambda functions, HTTP/HTTPS webhooks, Email (SMTP), and Mobile Push Notifications (APNs/FCM).
   - Can apply subscription filter policies to process only relevant message subsets.

```
+---------------+                    +-------------------------+ --> SQS Queue
|   Publisher   |                    |        SNS Topic        | --> AWS Lambda
| (Web Service) | --publish message->| (Logical Message Broker)| --> HTTPS Endpoint
+---------------+                    +-------------------------+ --> Email / SMS
```

<br>

## 🔥 Q6(b) [3 marks] How do the edge locations help Amazon CloudFront to provide services?

**Answer:**

Amazon CloudFront is a globally distributed Content Delivery Network (CDN). Edge Locations are geographically dispersed Points of Presence (PoPs) that optimize delivery via:

1. **Drastic Latency Reduction (Proximity Caching):**
   - Edge locations cache copies of static and frequently accessed dynamic web assets (HTML, CSS, JavaScript, images, streaming video) physically close to end-users worldwide.
   - A user request is automatically routed to the lowest-latency edge location via Anycast DNS routing, avoiding long-distance internet transits back to the origin server.
2. **Origin Shielding & Reduced Server Load:**
   - When an edge location satisfies a user request with a cache hit, the request terminates at the edge. The origin server (e.g., S3 bucket or EC2 web tier) is shielded from repetitive traffic spikes, significantly reducing compute and bandwidth costs.
3. **TLS/SSL Handshake Acceleration:**
   - SSL/TLS cryptographic handshakes terminate at the nearest edge location rather than traversing the global internet to the origin, accelerating HTTPS connection setup times.
4. **Enhanced Security & DDoS Mitigation:**
   - Edge locations integrate natively with AWS Shield and AWS WAF, filtering malicious traffic, SQL injection attacks, and volumetric Distributed Denial-of-Service (DDoS) attempts at the cloud perimeter before they reach the core infrastructure.

<br>

## 🔥 Q7(a) [2 marks] Can service oriented architecture (SOA) achieve interoperability? Explain.

**Answer:**

**Yes, Service Oriented Architecture (SOA) inherently achieves interoperability across heterogeneous platforms.**

It achieves this through:

1. **Universal Standardized Protocols:** SOA services interact using platform-agnostic, standardized application-layer communication protocols, predominantly HTTP/HTTPS, SOAP, and REST.
2. **Self-Describing Interface Contracts (WSDL / OpenAPI):**
   - Services expose formal contract definitions using standardized formats like Web Services Description Language (WSDL) or OpenAPI/Swagger.
   - These contracts define available operational methods, required input parameters, and expected output schemas in a platform-neutral XML or JSON syntax.
3. **Language and Platform Independence:**
   - A client written in Python running on Linux can seamlessly invoke an enterprise service written in Java on Windows Server or C# on .NET, because message exchanges consist strictly of standardized XML or JSON data envelopes.
4. **Loose Coupling:** Services remain black-box implementations. Internal implementation details, operating systems, and database schemas can be refactored independently without disrupting client interactions.

<br>

## 🔥 Q7(b) [3 marks] How can we create the scale up and scale down policies in Amazon Auto Scaling Group? Write the codes also.

**Answer:**

### Architectural Workflow:
1. Define an Auto Scaling Group with `MinSize`, `MaxSize`, and `DesiredCapacity`.
2. Create a **Scale-Out (Up)** policy that increments instance capacity by $+1$.
3. Create a **Scale-In (Down)** policy that decrements instance capacity by $-1$.
4. Bind AWS CloudWatch Alarms to the respective policy Amazon Resource Names (ARNs) to trigger policies based on CPU metric thresholds.

### Python Boto3 Implementation:

```python
import boto3

autoscaling = boto3.client('autoscaling', region_name='ap-south-1')
cloudwatch = boto3.client('cloudwatch', region_name='ap-south-1')

# 1. Define Scale-Out (Up) Policy: Add 1 instance
scale_out_response = autoscaling.put_scaling_policy(
    AutoScalingGroupName='production-asg',
    PolicyName='Step-Scale-Out-High-CPU',
    PolicyType='SimpleScaling',
    AdjustmentType='ChangeInCapacity',
    ScalingAdjustment=1,
    Cooldown=180
)
scale_out_arn = scale_out_response['PolicyARN']

# 2. Define Scale-In (Down) Policy: Remove 1 instance
scale_in_response = autoscaling.put_scaling_policy(
    AutoScalingGroupName='production-asg',
    PolicyName='Step-Scale-In-Low-CPU',
    PolicyType='SimpleScaling',
    AdjustmentType='ChangeInCapacity',
    ScalingAdjustment=-1,
    Cooldown=180
)
scale_in_arn = scale_in_response['PolicyARN']

# 3. Create CloudWatch Alarm to trigger Scale-Out when CPU >= 80%
cloudwatch.put_metric_alarm(
    AlarmName='High-CPU-Scale-Out-Alarm',
    MetricName='CPUUtilization',
    Namespace='AWS/EC2',
    Statistic='Average',
    Period=60,
    EvaluationPeriods=2,
    Threshold=80.0,
    ComparisonOperator='GreaterThanOrEqualToThreshold',
    AlarmActions=[scale_out_arn],
    Dimensions=[{'Name': 'AutoScalingGroupName', 'Value': 'production-asg'}]
)

# 4. Create CloudWatch Alarm to trigger Scale-In when CPU <= 30%
cloudwatch.put_metric_alarm(
    AlarmName='Low-CPU-Scale-In-Alarm',
    MetricName='CPUUtilization',
    Namespace='AWS/EC2',
    Statistic='Average',
    Period=120,
    EvaluationPeriods=2,
    Threshold=30.0,
    ComparisonOperator='LessThanOrEqualToThreshold',
    AlarmActions=[scale_in_arn],
    Dimensions=[{'Name': 'AutoScalingGroupName', 'Value': 'production-asg'}]
)

print("Scale-up and scale-down policies and alarms successfully provisioned.")
```

<br>

## 🔥 Q8(a) [2 marks] Explain the deployment design step of Cloud Component Model (CCM) with a diagram.

**Answer:**

In the Cloud Component Model (CCM), the **Deployment Design Step** translates high-level functional system components into concrete, multi-tier physical/virtual cloud infrastructure configurations.

### Key Deployment Variables Configured:
1. **Tier Topology:** Number and organization of application tiers (Web Tier, Application Logic Tier, Database Tier).
2. **Compute Capacity:** Specification of server count, CPU architecture, memory allocation, and OS distribution per tier.
3. **Storage & Database Provisioning:** Selection of block, object, or managed relational/NoSQL storage volumes.
4. **Network Interconnects:** Subnet layout, load balancer placements, security boundaries, and routing tables.

### CCM Iterative Lifecycle Diagram:

```
+-------------------------------------------------------------+
|               Cloud Component Model (CCM)                   |
+-------------------------------------------------------------+
                              |
                              v
                +---------------------------+
                |     Deployment Design     |  <----+
                | - Define Tier Hierarchy   |       |
                | - Provision Compute/RAM   |       |
                | - Configure Storage & Net |       |
                +---------------------------+       |
                              |                     | (Iterative
                              v                     |  Refinement
                +---------------------------+       |  Loop)
                |  Performance Evaluation   |       |
                | - Monitor Workload Levels |       |
                | - Measure Latency & TPS   |       |
                | - Identify Bottlenecks    |       |
                +---------------------------+       |
                              |                     |
                              v                     |
                +---------------------------+       |
                |   Deployment Refinement   |-------+
                | - Vertical / Horiz. Scale |
                | - Alternative Routing     |
                | - Caching / DB Replicas   |
                +---------------------------+
```

<br>

## 🔥 Q8(b) [3 marks] Suppose you need to create a document storage application. Explain the architecture design with a diagram. How can Django framework help?

**Answer:**

### 1. Multi-Tier Architecture Design:
A document storage application requires clear decoupling between compute logic, transactional document metadata, and binary file storage:

```
               [ Internet Clients / Web Browsers ]
                                |
                                v
               [ Elastic Load Balancer (ELB) ]
                                |
             +------------------+------------------+
             |                                     |
             v                                     v
+------------------------+             +------------------------+
| Django App Server 1    |             | Django App Server 2    |
| (Gunicorn / Nginx)     |             | (Gunicorn / Nginx)     |
+------------------------+             +------------------------+
             |                                     |
             +------------------+------------------+
                                |
        +-----------------------+-----------------------+
        |                                               |
        v                                               v
+------------------------+                     +------------------------+
|  Managed Relational DB |                     |  Amazon S3 Bucket      |
|  (Amazon RDS MySQL)    |                     |  (Object Storage)      |
|  - Users & Auth Credentials                  |  - Raw Binary Files    |
|  - Document Metadata:                        |  - PDF / DOCX Blobs    |
|    Title, Size, S3 Key,                      |  - Encrypted at Rest   |
|    Upload Timestamp, Owner                   |  - Highly Durable      |
+------------------------+                     +------------------------+
```

### 2. Role of the Django Framework:
Django implements the Model-Template-View (MTV) design pattern and accelerates development via:
1. **Object-Relational Mapping (ORM):** Enables clean, SQL-injection-safe database abstraction using Python classes:
   ```python
   class Document(models.Model):
       owner = models.ForeignKey(User, on_delete=models.CASCADE)
       file_name = models.CharField(max_length=255)
       s3_key = models.CharField(max_length=512)
       file_size = models.BigIntegerField()
       uploaded_at = models.DateTimeField(auto_now_add=True)
   ```
2. **Built-in Authentication & Authorization:** Comprehensive user management, password hashing (PBKDF2), role permissions, and session handling out of the box.
3. **Seamless Storage Backends (`django-storages` + `boto3`):** Intercepts standard file uploads and pipes file binary streams directly to Amazon S3 without exhausting application server local storage.
4. **Built-in Security Hardening:** Native protection against Cross-Site Request Forgery (CSRF), Cross-Site Scripting (XSS), and Clickjacking.

<br>

---

# 🐦‍🔥 MID SEMESTER EXAMINATION 2025

---

<br>

## 🔥 Q1(a) [3 marks] Explain the different types of Cloud Storages with examples.

**Answer:**

Cloud computing provides three primary storage paradigms, each tailored to distinct data access patterns:

| Storage Type | Architectural Structure | Access Protocol | Performance & Latency | Best Use Cases | Real-World Examples |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Object Storage** | Flat namespace; data stored as discrete objects containing payload, rich metadata, and a globally unique key. | HTTP/HTTPS RESTful APIs (GET, PUT, DELETE). | High throughput; higher latency (not intended for millisecond disk I/O). | Unstructured data, media assets, backups, archives, big data lakes. | Amazon S3, Google Cloud Storage, Azure Blob Storage. |
| **Block Storage** | Fixed-sized raw sectors/blocks addressed by Logical Unit Numbers (LUNs) without high-level metadata. | Native storage protocols (iSCSI, Fibre Channel, NVMe-oF). | Ultra-low latency; high IOPS; random read/write capability. | Virtual machine boot disks, operating system volumes, transactional databases. | Amazon EBS (Elastic Block Store), Azure Managed Disks, Google Persistent Disk. |
| **File Storage** | Hierarchical directory tree structure (nested folders, subfolders, individual files). | Network File System (NFS), Server Message Block (SMB). | Moderate latency; shared multi-client simultaneous read/write access. | Centralized content management, enterprise shared directories, legacy enterprise apps. | Amazon EFS (Elastic File System), Azure Files, Google Filestore. |

<br>

## 🔥 Q1(b) [2 marks] What are the roles of an user and provider for a Software as a Service (SaaS)?

**Answer:**

In the SaaS operational model, the application is hosted centrally and consumed over the web:

1. **Role of the SaaS User:**
   - **Application Consumption:** Interacts with the complete software solution through a web browser, mobile client, or lightweight API.
   - **Data Entry & Ownership:** Manages, creates, and maintains user data processed within the application.
   - **Identity & Access Administration:** Manages internal tenant credentials, user permissions, and passwords within their organizational domain.
   - **Zero Infrastructure Burden:** Borrows no responsibility for software installation, server provisioning, operating system maintenance, or runtime patching.
2. **Role of the SaaS Provider:**
   - **End-to-End Infrastructure Management:** Maintains the entire underlying stack: physical data centers, networking hardware, hypervisors, operating systems, and runtimes.
   - **Application Lifecycle & Development:** Authors source code, issues rolling software upgrades, performs database schema migrations, and repairs bugs.
   - **Security, High Availability & Disaster Recovery:** Guarantees contractual SLA commitments, executes automated multi-region data backups, and enforces regulatory compliance.

<br>

## 🔥 Q2(a) [3 marks] A company needs to handle massive video streaming traffic worldwide, scaling during peak times. Managing its own data centers was costly and limited. Explain how public cloud based deployment help here.

**Answer:**

A public cloud deployment solves the operational and financial challenges of global video streaming via:

1. **Global Content Distribution via CDN Edge PoPs:**
   - Services such as Amazon CloudFront or Cloudflare CDN deploy edge servers in hundreds of metropolitan areas worldwide.
   - Popular video segments (HLS/DASH fragments) are cached at edge locations, streaming directly to consumers with sub-30ms latency and drastically reducing cross-continent transit costs.
2. **Dynamic Elasticity & Auto Scaling for Peak Demand:**
   - On-premise data centers must be over-provisioned for worst-case peak traffic (e.g., live sports tournaments), leaving servers idle during troughs.
   - Public cloud Auto Scaling dynamically provisions and terminates thousands of streaming instances in minutes, matching capacity precisely to real-time viewer demand.
3. **Transition from CapEx to OpEx:**
   - Eliminates millions of dollars in upfront Capital Expenditures (buying physical servers, cooling systems, multi-gigabit fiber lines).
   - Operates on an Operational Expenditure (OpEx) Pay-As-You-Go model—paying only for compute hours consumed and petabytes delivered.
4. **Elastic Cloud Media Transcoding:**
   - Managed transcoding services (e.g., AWS Elemental MediaConvert) elastically transcode high-resolution master video files concurrently into multiple bitrates and formats (1080p, 720p, mobile) without purchasing dedicated hardware transcoders.
5. **Durable, Tiered Storage Lifecycle:**
   - Videos are stored in Amazon S3. Automated lifecycle policies migrate historical, low-traffic catalog videos to low-cost archival tiers (S3 Glacier / Deep Archive), optimizing storage economics.

<br>

## 🔥 Q2(b) [2 marks] What do you mean by Virtual Machine Snapshot?

**Answer:**

A **Virtual Machine Snapshot** is a point-in-time, frozen representation of the complete state, storage data, and hardware configuration of an active virtual machine:

### Captured Components:
1. **Volatile Memory State (RAM):** The contents of the running VM's memory and CPU register states (allowing the VM to resume instantly in the exact operational state).
2. **Virtual Disk State:** A delta difference disk is initialized; all subsequent block modifications are written to the delta file, preserving the original virtual disk as read-only.
3. **Virtual Hardware Configuration:** Complete snapshot of virtual NICs, CPU mappings, BIOS settings, and attached drive definitions.

### Practical Engineering Use Cases:
- **Safety Rollback Point:** Captured immediately prior to applying complex software patches, kernel updates, or database schema alterations; allows near-instantaneous restoration if errors occur.
- **VM Cloning & Templating:** Used to instantiate identical testing and staging environments.

<br>

## 🔥 Q3(a) [3 marks] Explain the Memory Transfer Overheads that are present when a VM migration is performed.

**Answer:**

Live Virtual Machine Migration moves a running VM between physical host servers without significant service interruption. The dominant overhead arises during memory synchronization (e.g., Pre-Copy Live Migration):

```
Time -------------------------------------------------------------------->
Round 1: Copy full physical RAM (e.g., 16 GB)
         [========== All Memory Pages Transferred ==========]
Round 2: Re-transmit Dirty Pages (pages modified during Round 1)
         [==== Dirty Pages Transferred ====]
Round 3: Re-transmit remaining Dirty Pages
         [== Dirty Pages ==]
Stop-and-Copy: VM Paused -> Final Dirty Pages -> State Resume
         [|] Downtime
```

### Key Memory Transfer Overheads:
1. **Iterative Pre-Copy Retransmission Overhead:**
   - In round 1, all physical memory pages are copied from source to target.
   - While transmission occurs, the guest OS continues executing and modifies memory blocks. These modified locations are termed **Dirty Pages**.
   - Subsequent iteration rounds must re-transmit these dirty pages. If the application has a high memory write rate, iterations multiply, consuming massive network bandwidth.
2. **Dirty Page Rate vs Network Bandwidth Convergence Risk:**
   - If the rate of memory page modification exceeds the network transmission bandwidth ($R_{dirty} \ge B_{network}$), the iterative transfer **cannot converge**. The migration may loop indefinitely, degrading network throughput for co-located workloads.
3. **Stop-and-Copy Blackout Downtime Overhead:**
   - Once dirty pages drop below a convergence threshold, the hypervisor suspends the VM on the source node, copies CPU registers and final memory deltas, and resumes execution on the target.
   - This phase induces instantaneous service latency and temporary TCP connection stall.
4. **Host Hypervisor CPU Overhead:**
   - Memory page-tracking mechanisms (shadow page tables or hardware-nested paging write-protection bits) impose continuous CPU context-switch overhead on the hypervisor during the migration lifecycle.

<br>

## 🔥 Q3(b) [2 marks] What are the advantages of a Hypervisor? Explain.

**Answer:**

A Hypervisor (Virtual Machine Monitor) delivers fundamental architectural advantages in modern computing:

1. **Hardware Consolidation & Resource Efficiency:**
   - Multiple distinct operating systems run simultaneously on a single physical host.
   - Elevates enterprise physical hardware utilization from typical historical baselines of $10\%-15\%$ up to $70\%-80\%$, drastically lowering equipment, electrical power, and cooling costs.
2. **Strict Fault and Security Isolation:**
   - Each VM operates inside an isolated sandbox. A catastrophic operating system crash, kernel panic, or malware infection inside one guest VM cannot propagate across hypervisor boundaries to compromise adjacent VMs.
3. **Hardware Abstraction & Portability:**
   - The hypervisor presents uniform virtual hardware interfaces to guest operating systems.
   - VMs are encapsulated as simple file disk images, enabling live migration, instant automated backups, and hardware-independent portability across differing server generations.
4. **Rapid, Programmable Provisioning:**
   - Eliminates physical hardware procurement lead times; virtual server instances can be programmatically spun up or destroyed in seconds via API calls.

<br>

## 🔥 Q4(a) [3 marks] Write a python program using boto to add an inbound rule in a security group.

**Answer:**

```python
import boto3
from botocore.exceptions import ClientError

def add_inbound_security_rule(group_id, port, protocol="tcp", cidr_ip="0.0.0.0/0"):
    """
    Adds an inbound (ingress) rule to an existing AWS EC2 Security Group using Boto3.
    """
    ec2_client = boto3.client('ec2', region_name='ap-south-1')
    
    try:
        response = ec2_client.authorize_security_group_ingress(
            GroupId=group_id,
            IpPermissions=[
                {
                    'IpProtocol': protocol,
                    'FromPort': port,
                    'ToPort': port,
                    'IpRanges': [
                        {
                            'CidrIp': cidr_ip,
                            'Description': f'Allow inbound traffic on port {port} from {cidr_ip}'
                        }
                    ]
                }
            ]
        )
        print(f"Successfully authorized port {port} for Security Group {group_id}")
        return response
    except ClientError as e:
        print(f"Failed to authorize security group ingress: {e}")
        raise

if __name__ == "__main__":
    # Example execution: Open HTTP Port 80 to the world
    SECURITY_GROUP_ID = "sg-0123456789abcdef0"
    add_inbound_security_rule(group_id=SECURITY_GROUP_ID, port=80)
```

<br>

## 🔥 Q4(b) [2 marks] Why do we need to perform deployment refinement for a cloud application?

**Answer:**

Deployment Refinement is the essential iterative stage following initial deployment and performance evaluation in the Cloud Component Model (CCM). It is necessary because:

1. **Bridging Initial Design vs Real-World Gaps:** Initial deployment capacity models are constructed using theoretical assumptions. Real-world user traffic patterns, concurrent request concurrency, and database query locks reveal unforeseen performance bottlenecks that require architectural tuning.
2. **Cost-to-Performance Optimization:** Prevents **over-provisioning** (which causes unnecessary financial expenditure on idle resources) and **under-provisioning** (which causes high latency, packet drops, and SLA breaches).
3. **Architectural Scaling Selection:** Evaluates whether bottlenecked tiers require **Vertical Scaling** (increasing instance size for transactional databases) or **Horizontal Scaling** (adding stateless web/application nodes behind a load balancer).
4. **Identification of Component Enhancements:** Dictates the introduction of caching layers (Redis/Memcached), read-replica databases, asynchronous task queues (Celery/SQS), or revised load-balancing algorithms to achieve optimal efficiency.

<br>

## 🔥 Q5(a) [3 marks] How Role-Based Access Control (RBAC) improves the Identity and Access Control in cloud? Explain.

**Answer:**

Role-Based Access Control (RBAC) governs resource authorization by binding permissions to predefined organizational **roles** rather than directly to individual user accounts:

```
[ User Accounts ] ----------> [ Assigned Roles ] ----------> [ Fine-Grained Permissions ]
- Alice (DevOps)             - 'DevOps-Admin'               - ec2:*
- Bob   (Junior Dev)         - 'ReadOnly-Analyst'           - s3:GetObject
- Carol (Auditor)            - 'Billing-Manager'            - cloudwatch:GetMetricData
```

### RBAC Improvements to Cloud Identity Governance:
1. **Implementation of Principle of Least Privilege:**
   - Users inherit only the precise privileges assigned to their designated functional role. Unauthorized actions across other cloud compartments are systematically denied by default.
2. **Scalable User Lifecycle Administration:**
   - In enterprise systems with thousands of employees, modifying individual user permissions is error-prone. With RBAC, when an employee changes job responsibilities, the administrator simply updates their role membership; all associated cloud permissions update instantaneously.
3. **Enforcement of Separation of Duties:**
   - Distinct roles prevent toxic privilege combinations. For instance, developers can be prohibited from possessing production deployment privileges, and financial auditors are restricted from mutating compute infrastructure.
4. **Streamlined Compliance Auditing:**
   - Simplifies security compliance audits (e.g., SOC2, ISO 27001). Security officers inspect a finite matrix of role permissions rather than auditing disparate configurations across individual users.

<br>

## 🔥 Q5(b) [2 marks] What do you mean by Southbound Interface and Northbound Interface in Software Defined Networking?

**Answer:**

Software Defined Networking (SDN) relies on two standardized programmatic communication boundaries:

```
+-------------------------------------------------------+
|              SDN Business Applications                |
|           (Firewall, QoS, Traffic Balancer)           |
+-------------------------------------------------------+
                           |
                           |  Northbound Interface (REST / Open APIs)
                           v
+-------------------------------------------------------+
|             Centralized SDN Controller                |
|                  (Control Plane)                      |
+-------------------------------------------------------+
                           |
                           |  Southbound Interface (OpenFlow Protocol)
                           v
+-------------------------------------------------------+
|          Data Plane Network Forwarding Nodes          |
|              (OpenFlow Switches / Routers)            |
+-------------------------------------------------------+
```

1. **Northbound Interface:**
   - The programmable API boundary between **SDN Applications** and the **SDN Controller**.
   - Typically implemented using RESTful web services or Java/Python APIs.
   - Allows network engineers and applications to articulate high-level network behaviors (e.g., routing path generation, security policies, QoS enforcement) without interacting with physical hardware.
2. **Southbound Interface:**
   - The standardized protocol link between the **SDN Controller** and underlying **Network Switching Hardware (Data Plane)**.
   - Predominantly implemented via the **OpenFlow** protocol.
   - Transmits flow-table rules, packet forwarding instructions, and configuration updates from the controller down to the switches, and conveys telemetry/packet-in events back up.

<br>

## 🔥 Q6(a) [3 marks] How can map reduce help in big data processing? Give an example.

**Answer:**

### How MapReduce Solves Big Data Processing:
1. **Divide-and-Conquer Parallel Execution:** Partitions immense datasets into independent splits processed concurrently across a distributed cluster of worker nodes.
2. **Data Locality Principle:** Computation code is scheduled on the exact physical node where the data block resides in the distributed filesystem (e.g., HDFS), circumventing saturating network switches.
3. **Automatic Fault Tolerance:** If a worker node fails during execution, the master node detects heartbeat loss and re-schedules the failed Map task on an alternate node containing a replicated data block.

### Execution Phases Example: Word Count over Distributed Web Logs

```
Input Data: "cloud computing architecture" & "cloud data computing"

1. MAP PHASE (Worker Nodes execute in parallel):
   Worker 1 processes Split 1 -> ("cloud", 1), ("computing", 1), ("architecture", 1)
   Worker 2 processes Split 2 -> ("cloud", 1), ("data", 1), ("computing", 1)

2. SHUFFLE & SORT PHASE (Cluster Network Partitioning by Key):
   Partitioner routes identical keys to the same Reduce worker:
   "architecture" -> [1]
   "cloud"        -> [1, 1]
   "computing"    -> [1, 1]
   "data"         -> [1]

3. REDUCE PHASE (Worker Nodes aggregate values):
   Reduce Worker output:
   ("architecture", 1)
   ("cloud", 2)
   ("computing", 2)
   ("data", 1)
```

<br>

## 🔥 Q6(b) [2 marks] What are the different components of service level agreement (SLA)?

**Answer:**

A formal Service Level Agreement (SLA) comprises the following structural components:

1. **Purpose & Scope:** Outlines the legal intent of the contract, specifies the exact services covered, and defines valid performance evaluation boundaries.
2. **Parties Involved:** Identifies the formal legal entities involved (Cloud Service Provider and Cloud Service Consumer).
3. **Service Level Objectives (SLOs):** Measurable quantitative performance thresholds contracted by the provider, including:
   - *Availability / Uptime Percentage:* (e.g., $99.99\%$ monthly availability).
   - *Latency:* (e.g., API response time $\le 100\text{ ms}$ for the 95th percentile).
   - *Throughput:* (e.g., minimum guaranteed transactions per second).
4. **Service Credit & Penalty Mechanisms:** Quantifies financial compensation or billing credit percentages awarded to the customer upon verified SLO violations.
5. **Exclusions & Restrictions:** Identifies scenarios where SLA guarantees do not apply (e.g., scheduled maintenance windows, force majeure events, customer misconfigurations).
6. **Monitoring and Reporting Protocol:** Defines how metrics are logged, audited, and submitted for breach verification.

<br>

## 🔥 Q7(a) [2 marks] Explain the functionality of three OpenStack components.

**Answer:**

OpenStack is a modular open-source Infrastructure-as-a-Service (IaaS) cloud management platform. Three foundational components include:

1. **Nova (Compute Service):**
   - The primary computing engine responsible for managing the lifecycle of virtual machine instances (provisioning, scheduling, starting, stopping, and terminating).
   - Interfaces with diverse hypervisors (KVM, QEMU, VMware ESXi) via standard drivers.
2. **Swift (Object Storage Service):**
   - Provides distributed, eventually consistent, scalable object storage for petabytes of unstructured data (similar to Amazon S3).
   - Automatically replicates data objects across multiple physical drives, servers, and zones to guarantee extreme durability and fault tolerance.
3. **Neutron (Networking Service):**
   - Delivers Software Defined Networking (SDN) capabilities across OpenStack compute instances.
   - Programmatically provisions virtual networks, subnets, routers, floating public IP addresses, VLANs, and firewall security groups.

<br>

## 🔥 Q7(b) [3 marks] How Amazon Simple Queue Service (SQS) works? Can it reduce tight coupling?

**Answer:**

### 1. Architectural Workflow of Amazon SQS:
Amazon SQS is a fully managed, distributed message queuing service operating on an asynchronous producer-consumer model:
1. **Message Ingestion:** An upstream producer application generates a message payload (up to 256 KB) and issues a `SendMessage` API call to an SQS queue.
2. **Redundant Persistence:** SQS replicates the message across multiple availability zone storage servers for high durability.
3. **Consumer Polling & Visibility Timeout:** A downstream worker pulls messages via `ReceiveMessage`. SQS marks the message invisible to other concurrent consumers for a defined **Visibility Timeout** period.
4. **Acknowledgment & Deletion:** Upon successful processing, the worker issues a `DeleteMessage` call to purge the message from the queue, preventing duplicate reprocessing.

```
[ Upstream Producer ] ----SendMessage----> [ SQS Distributed Queue ]
                                                  |
                                            ReceiveMessage (Locks message)
                                                  v
[ Downstream Worker ] <-------------------+-------+
        |
   Processes Job
        |
        v
 issues DeleteMessage
```

### 2. Elimination of Tight Coupling:
**Yes, SQS systematically eliminates architectural tight coupling through:**
- **Temporal Decoupling:** The producer and consumer do not need to be active simultaneously. If downstream order processing services crash, orders safely buffer in the queue until services recover.
- **Traffic Smoothing (Load Leveling):** Protects downstream databases from sudden traffic spikes by acting as a shock-absorbing buffer; workers process messages at a controlled, sustainable rate.
- **Independent Scaling:** Compute tiers scale autonomously—producers scale on web traffic, while worker instances scale on queue depth (`ApproximateNumberOfMessagesVisible`).

<br>

## 🔥 Q8(a) [3 marks] A company wants to develop a blog platform where users can: (i) Create, edit, and delete blog posts (ii) View posts (iii) Comment on posts (iv) Like posts. How can you design this system using MVC Architecture?

**Answer:**

The Model-View-Controller (MVC) architectural pattern decomposes the blog platform into three distinct, loosely coupled layers:

```
[ User Browser / Client ]
       |         ^
(HTTP  |         | (HTML / JSON
Request)         |  Response)
       v         |
+-------------------------------------------------------+
|                     CONTROLLER                        |
| - URL Routing & Request Dispatch                      |
| - Authentication Verification                         |
| - Input Validation & Business Logic Routing           |
+-------------------------------------------------------+
       |                                   |
       | Mutates / Queries                 | Passes Render Data
       v                                   v
+------------------------+      +------------------------+
|         MODEL          |      |          VIEW          |
| - Relational Entities  |      | - Jinja2/HTML Template |
| - ORM Logic            |      | - UI Representation    |
| - Database Schema      |      | - Markdown Renderer    |
+------------------------+      +------------------------+
       |
       v
[ Database Storage ]
```

### 1. Model Layer (Data Schema & Relationships):
```python
class User(models.Model):
    user_id = models.AutoField(primary_key=True)
    username = models.CharField(max_length=50, unique=True)
    email = models.EmailField(unique=True)

class Post(models.Model):
    post_id = models.AutoField(primary_key=True)
    author = models.ForeignKey(User, on_delete=models.CASCADE)
    title = models.CharField(max_length=200)
    content = models.TextField()
    created_at = models.DateTimeField(auto_now_add=True)

class Comment(models.Model):
    comment_id = models.AutoField(primary_key=True)
    post = models.ForeignKey(Post, on_delete=models.CASCADE, related_name="comments")
    author = models.ForeignKey(User, on_delete=models.CASCADE)
    comment_text = models.TextField()
    created_at = models.DateTimeField(auto_now_add=True)

class Like(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    post = models.ForeignKey(Post, on_delete=models.CASCADE)
    class Meta:
        unique_together = ('user', 'post')  # Prevents duplicate likes
```

### 2. Controller Layer (HTTP Endpoints & Request Orchestration):
- `POST /posts/create` $\rightarrow$ Validates user session; parses title/content; invokes `Post.objects.create()`.
- `GET /posts/{id}` $\rightarrow$ Queries `Post` by ID; loads associated comments and like count; dispatches to View.
- `PUT /posts/{id}/edit` $\rightarrow$ Confirms requesting user equals `post.author`; applies modifications.
- `DELETE /posts/{id}` $\rightarrow$ Verifies ownership; issues delete cascade.
- `POST /posts/{id}/comment` $\rightarrow$ Inserts a new `Comment` record linked to user and post.
- `POST /posts/{id}/like` $\rightarrow$ Creates or deletes a `Like` record atomically.

### 3. View Layer (Presentation Logic):
- Renders sanitized HTML templates (`post_detail.html`, `post_feed.html`, `editor.html`) or serializes clean RESTful JSON payloads for single-page client applications.

<br>

## 🔥 Q8(b) [2 marks] What factors would you consider when you design a Cloud Application? Explain.

**Answer:**

When architecting an enterprise cloud-native application, engineers must prioritize the following core design considerations:

1. **Elastic Scalability:** System components must be stateless wherever possible, enabling seamless horizontal scale-out across auto-scaling compute pools as workloads fluctuate.
2. **High Availability & Fault Tolerance:** Elimination of single points of failure (SPOF) through multi-availability zone deployments, redundant load balancing, and automated database failover.
3. **End-to-End Security & Compliance:** Enforcement of defense-in-depth: network perimeter firewalls, encryption at rest and in transit, strict IAM least-privilege policies, and zero-trust authentication.
4. **Performance & Low Latency:** Caching frequently accessed data via CDN edge locations (CloudFront) and in-memory key-value stores (Redis) to mitigate database I/O bottlenecks.
5. **Cost Optimization:** Architectural rightsizing, leveraging spot instances for batch workloads, and using tiered storage lifecycle policies to minimize cloud expenses.
6. **Maintainability & Observability:** Comprehensive telemetry instrumentation (metrics, distributed tracing, centralized logging) coupled with automated CI/CD deployment pipelines.

<br>

---



# 🐦‍🔥 END SEMESTER EXAMINATION 2024

---

<br>

## 🔥 Q1(a) [2 points] Map Reduce can help in achieving scalability. Justify how.

**Answer:**

MapReduce achieves horizontal scalability through three foundational architectural principles:

1. **Compute-to-Data (Data Locality):** In traditional distributed systems, large datasets are transferred across the network to centralized compute nodes, causing severe network switch bottlenecks. MapReduce moves computation to the data: Map tasks are scheduled directly on the physical cluster nodes (DataNodes) that already store the required 128 MB data blocks locally. Network transfer is strictly minimized.
2. **Shared-Nothing Parallel Partitioning:** Input datasets are divided into independent chunks (input splits). Thousands of Mappers process these chunks concurrently without requiring shared memory or cross-node synchronization locks.
3. **Linear Performance Scaling with Commodity Hardware:** Throughput scales linearly: adding $N$ additional commodity worker nodes to a Hadoop cluster proportionally increases Map and Reduce processing capacity without modifying application source code.

<br>

## 🔥 Q1(b) [4 points] We have a server log having different HTTP status codes (e.g., 200, 404). Write pseudocodes for mapper and reducer to find the count of different HTTP status codes.

**Answer:**

### Mapper Pseudocode:
The Mapper parses each log entry line from standard input, extracts the HTTP status code (using string splitting or regex matching), and emits the status code as the key with an integer count of 1 as the value.

```python
import sys
import re

# Regex matching standard Apache/Nginx combined log HTTP status code field
LOG_PATTERN = re.compile(r'"\s+(\d{3})\s+')

def mapper():
    for line in sys.stdin:
        line = line.strip()
        match = LOG_PATTERN.search(line)
        if match:
            status_code = match.group(1)
            # Emit key and value separated by a tab
            sys.stdout.write(f"{status_code}\t1\n")

if __name__ == "__main__":
    mapper()
```

### Reducer Pseudocode:
Hadoop automatically sorts and groups emitted keys during the Shuffle phase. The Reducer reads intermediate key-value pairs sorted by `status_code`, sums the counts for identical codes, and prints the aggregated totals.

```python
import sys

def reducer():
    current_status = None
    current_count = 0

    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        
        status_code, count_str = line.split('\t', 1)
        count = int(count_str)

        if current_status == status_code:
            current_count += count
        else:
            if current_status is not None:
                # Output final aggregated count for previous status code
                sys.stdout.write(f"{current_status}\t{current_count}\n")
            current_status = status_code
            current_count = count

    # Flush the last status code aggregation
    if current_status is not None:
        sys.stdout.write(f"{current_status}\t{current_count}\n")

if __name__ == "__main__":
    reducer()
```

<br>

## 🔥 Q2(a) [3 points] Write about three main features of Hadoop Distributed File System (HDFS).

**Answer:**

1. **Large Block-Based Distribution (Default 128 MB / 256 MB):**
   Unlike traditional OS filesystems that manage data in small 4 KB blocks, HDFS divides multi-gigabyte and terabyte files into large contiguous blocks (default 128 MB). This amortizes disk seek time, ensuring that data access is dominated by sustained streaming transfer rates.
2. **Replication & Rack-Aware Fault Tolerance:**
   Every block is automatically replicated across multiple physical nodes (default replication factor = 3). HDFS applies **rack awareness**: Replica 1 is placed on the local DataNode, Replica 2 on a remote rack, and Replica 3 on a different node in that same remote rack. This guarantees high availability against both individual machine failures and entire rack switch outages.
3. **Write-Once, Read-Many (WORM) Consistency Model:**
   Files in HDFS cannot be arbitrarily modified in-place at random offsets. Once created and written, files are immutable, though appending data to the end of a file is supported. This write-once paradigm simplifies distributed caching, eliminates cache coherence overhead, and enables high-throughput concurrent reads.

<br>

## 🔥 Q2(b) [2 points] Write the differences between HDFS and HBase.

**Answer:**

| 🌟 Dimension | Hadoop Distributed File System (HDFS) | Apache HBase |
| :--- | :--- | :--- |
| **System Classification** | Distributed File System | Distributed Column-Oriented NoSQL Database |
| **Data Access Pattern** | Sequential batch read/write access | Low-latency, random read/write access |
| **Data Modification** | Append-only; no in-place record updates or deletes | In-place record updates and row-level deletes (via tombstone markers) |
| **Latency Profile** | High latency (seconds to minutes via MapReduce) | Real-time, low latency (sub-5 milliseconds per record) |
| **Underlying Layer** | Runs on commodity hardware local filesystems | Runs on top of HDFS (persists data as HFiles) |

<br>

## 🔥 Q2(c) [2 points] What are the different schedulers available in Hadoop?

**Answer:**

Hadoop YARN provides three pluggable schedulers within the ResourceManager:

1. **FIFO Scheduler (First-In, First-Out):** The simplest scheduler. Jobs are placed in a single queue and executed strictly in the order of their arrival. Suffers from **head-of-line blocking** where long batch jobs delay small interactive queries.
2. **Capacity Scheduler (Developed by Yahoo):** Designed for multi-tenant enterprises. Resources are partitioned into dedicated departmental queues, each guaranteed a minimum capacity percentage. Unused capacity can be dynamically borrowed by active queues.
3. **Fair Scheduler (Developed by Facebook):** Dynamically allocates resources such that all running applications receive, on average, an equal share of cluster capacity over time.

<br>

## 🔥 Q3(a) [2 points] How Apache Hive performs integration with Hadoop Ecosystem?

**Answer:**

Apache Hive integrates with the Hadoop ecosystem through three foundational architectural mechanisms:

1. **Schema-on-Read over HDFS Storage:** Hive does not store data in proprietary database formats. Instead, raw data files (CSV, JSON, ORC, Parquet) reside directly in HDFS. Hive uses **SerDe (Serializer/Deserializer)** interfaces to interpret raw bytes according to schema definitions upon query execution.
2. **Metadata Abstraction via Hive Metastore:** Hive maintains structural table definitions, column types, partitions, and HDFS physical storage locations in a centralized relational database (Metastore).
3. **Query Compilation to Distributed Execution Engines:** The Hive Driver and Compiler parse declarative SQL queries (HiveQL), construct an optimized execution DAG, and automatically compile them into physical **MapReduce, Apache Tez, or Apache Spark** jobs executed across YARN cluster nodes.

<br>

## 🔥 Q3(b) [3 points] Write a user-defined function (UDF) in Apache Pig to find the length of a text field (say name) for each record of a dataset.

**Answer:**

### Python UDF Implementation:
```python
# filename: text_udf.py
from pig_util import outputSchema

@outputSchema("name_length:int")
def calculate_name_length(text_field):
    """Computes the length of the string field."""
    if text_field is None:
        return 0
    return len(str(text_field).strip())
```

### Apache Pig Latin Script:
```pig
-- Register the Python UDF file
REGISTER 'text_udf.py' USING jython AS my_udf;

-- Load the dataset from HDFS
records = LOAD '/user/hadoop/customer_records.txt' 
          USING PigStorage(',') 
          AS (id:int, name:chararray, city:chararray);

-- Apply the custom UDF to each record
projected_data = FOREACH records GENERATE 
                    id, 
                    name, 
                    my_udf.calculate_name_length(name) AS name_length, 
                    city;

-- Display the results to standard output
DUMP projected_data;
```

<br>

## 🔥 Q4(a) [3 points] Explain the architecture of Apache Spark with a diagram.

**Answer:**

### Architectural Overview:
Apache Spark follows a master-slave distributed computing architecture. It eliminates MapReduce disk I/O bottlenecks by maintaining working datasets in cluster RAM across iterative operations.

```
+-----------------------------------------------------------------------------------+
|                            APACHE SPARK ARCHITECTURE                              |
+-----------------------------------------------------------------------------------+
+------------------------------------------------------------------+
|                          DRIVER PROGRAM                          |
|  - SparkContext / SparkSession                                   |
|  - DAGScheduler (Converts RDD operations into physical stages)   |
|  - TaskScheduler (Dispatches tasks to workers)                   |
+------------------------------------------------------------------+
                                  |
                                  v
+------------------------------------------------------------------+
|                         CLUSTER MANAGER                          |
|  (Hadoop YARN / Kubernetes / Apache Mesos / Spark Standalone)    |
+------------------------------------------------------------------+
                 |                                                 |
                 v                                                 v
+----------------------------------+             +----------------------------------+
|           WORKER NODE 1          |             |           WORKER NODE 2          |
| +------------------------------+ |             | +------------------------------+ |
| |          EXECUTOR 1          | |             | |          EXECUTOR 2          | |
| | - In-Memory Cache (RAM)      | |             | | - In-Memory Cache (RAM)      | |
| | - Task 1 | Task 2            | |             | | - Task 3 | Task 4            | |
| +------------------------------+ |             | +------------------------------+ |
+----------------------------------+             +----------------------------------+
```

### Core Components:
1. **Driver Program:** Hosts the application's `main()` function, instantiates `SparkSession`, constructs the execution DAG, and coordinates task scheduling.
2. **Cluster Manager:** Allocates physical cluster compute resources (CPU cores and RAM).
3. **Worker Nodes:** Cluster machines that launch and host executor processes.
4. **Executors:** Dedicated JVM processes running on worker nodes. Executors run tasks concurrently across threads and maintain in-memory storage for cached RDD partitions.
5. **Tasks:** Individual units of physical work executed over a single data partition.

<br>

## 🔥 Q4(b) [3 points] What are the functions of collect() and map() in Apache Spark?

**Answer:**

| 🌟 Feature | `map()` Function | `collect()` Function |
| :--- | :--- | :--- |
| **Operation Type** | **Transformation** (Lazy) | **Action** (Eager) |
| **Execution Trigger** | Does NOT trigger immediate computation; only records transformation in DAG lineage. | **Triggers immediate execution** of the entire DAG lineage across the cluster. |
| **Return Value** | Returns a **new RDD** representing transformed elements (`RDD[U]`). | Returns an array containing **all dataset elements** to the Driver program memory. |
| **Execution Location** | Executed in parallel by Worker Executors across distributed partitions. | Executes distributed tasks and pulls all results into the centralized **Driver**. |
| **Memory Risk** | Low memory footprint; processes data streaming partition-by-partition. | **High Out-Of-Memory (OOM) Risk** if dataset size exceeds Driver RAM capacity. |
| **Functionality** | Applies a user function element-wise: $f(x) \to y$. | Retrieves final computed dataset for client inspection or local file export. |

<br>

## 🔥 Q5(a) [3 points] How does Single Sign-On (SSO) based authentication work?

**Answer:**

Single Sign-On (SSO) is a centralized authentication framework that allows users to authenticate once with an Identity Provider (IdP) and gain seamless access to multiple independent Service Providers (SPs) without repeatedly entering passwords.

### Step-by-Step Workflow (SAML 2.0 Web SSO):
1. **Resource Request:** The user navigates to a protected cloud application (Service Provider, e.g., AWS Console).
2. **Authentication Challenge:** The Service Provider detects no active session, generates an encoded XML `<AuthnRequest>`, and redirects the user's browser to the enterprise **Identity Provider (IdP)** (e.g., Okta, Azure AD).
3. **User Authentication:** The IdP prompts the user for corporate credentials (username, password, MFA). The IdP verifies credentials against the central user directory.
4. **Assertion Generation:** Upon successful verification, the IdP generates a cryptographically signed XML document called a **SAML Assertion** containing user identity attributes (e.g., email, role) and expiration timestamps.
5. **Token POST:** The user's browser forwards the signed SAML Assertion token to the Service Provider's Assertion Consumer Service (ACS).
6. **Signature Verification & Access Grant:** The Service Provider verifies the digital signature using the IdP's pre-configured Public Key Certificate, establishes an authenticated session, and grants access.

<br>

## 🔥 Q5(b) [3 points] Asymmetric encryption can help in securing data in cloud. Justify.

**Answer:**

Asymmetric encryption utilizes a mathematically linked key pair: a **Public Key** (openly published) and a **Private Key** (kept strictly confidential by the owner). It secures cloud data through three critical capabilities:

1. **Elimination of Secret Key Distribution Vulnerability:** In symmetric encryption, communicating parties must share a single secret key. Distributing secret keys over untrusted public networks is vulnerable to interception. Asymmetric encryption eliminates this risk: anyone can encrypt data using the recipient's public key, but **only the intended recipient** holding the matching private key can decrypt it.
2. **Secure Key Exchange for Hybrid Cryptosystems:** Asymmetric cryptography (e.g., RSA, ECDHE) is used in TLS/SSL to securely negotiate ephemeral symmetric session keys (AES-256) between cloud clients and cloud load balancers over public networks.
3. **Digital Signatures & Identity Verification:** Cloud administrators and compute services use asymmetric private keys to sign API requests, code packages, and access tokens (JWTs), ensuring non-repudiation, tamper detection, and identity verification.

<br>

## 🔥 Q6(a) [3 points] You have a dataset having many features of the objects. Write map and reduce functions (pseudo-codes) to perform grouping of these objects.

**Answer:**

To group objects across multiple features, the Mapper extracts the desired grouping attributes, concatenates them into a unified **composite key**, and emits the remaining object data as the value. The Reducer collects all objects belonging to each composite key group.

### Grouping Mapper Pseudocode:
```python
import sys
import json

# Grouping by multiple features: e.g., 'category' and 'region'
GROUP_ATTRIBUTES = ["category", "region"]

def grouping_mapper():
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        record = json.loads(line)
        
        # Form composite key from specified features
        composite_key = "#".join(str(record.get(attr, "")) for attr in GROUP_ATTRIBUTES)
        
        # Emit composite key and entire object payload
        print(f"{composite_key}\t{json.dumps(record)}")

if __name__ == "__main__":
    grouping_mapper()
```

### Grouping Reducer Pseudocode:
```python
import sys
import json

def grouping_reducer():
    current_key = None
    grouped_objects = []

    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        composite_key, record_str = line.split('\t', 1)
        record = json.loads(record_str)

        if current_key == composite_key:
            grouped_objects.append(record)
        else:
            if current_key is not None:
                # Output group key and the collection of matching objects
                print(f"{current_key}\t{json.dumps(grouped_objects)}")
            current_key = composite_key
            grouped_objects = [record]

    if current_key is not None:
        print(f"{current_key}\t{json.dumps(grouped_objects)}")

if __name__ == "__main__":
    grouping_reducer()
```

<br>

## 🔥 Q6(b) [3 points] Explain with an example how Apache Spark helps in classifying big data.

**Answer:**

Supervised classification of big data requires training predictive models over millions of high-dimensional records. Apache Spark achieves this via its **MLlib** library, which leverages in-memory caching and distributed linear algebra to scale algorithms (Logistic Regression, Random Forests, Gradient Boosted Trees) across cluster executors.

### Example: Predicting Customer Churn using PySpark:
```python
from pyspark.sql import SparkSession
from pyspark.ml.feature import VectorAssembler
from pyspark.ml.classification import LogisticRegression

# 1. Initialize SparkSession
spark = SparkSession.builder.appName("ChurnClassification").getOrCreate()

# 2. Ingest massive distributed dataset from HDFS
df = spark.read.parquet("hdfs://cluster/data/telecom_churn.parquet")

# 3. Assemble multiple numerical features into a single feature vector
feature_cols = ["account_length", "monthly_charges", "customer_service_calls"]
assembler = VectorAssembler(inputCols=feature_cols, outputCol="features")
vectorized_df = assembler.transform(df)

# 4. Train-Test Split (80% Training, 20% Testing)
train_data, test_data = vectorized_df.randomSplit([0.8, 0.2], seed=42)

# 5. Distributed Model Training (Logistic Regression)
lr = LogisticRegression(featuresCol="features", labelCol="churned", maxIter=20)
model = lr.fit(train_data)

# 6. Parallel Inference over Unseen Data
predictions = model.transform(test_data)
predictions.select("features", "churned", "prediction", "probability").show(5)
```

**Why Spark excels:**
- Features are transformed in parallel across partitions.
- Iterative optimization (L-BFGS gradient descent) retains intermediate weight vectors in executor RAM rather than reading/writing to disk each iteration.

<br>

## 🔥 Q7(a) [4 points] How can we distribute multimedia files globally using cloud computing? How can cloud perform media transcoding here?

**Answer:**

### 1. Global Distribution of Multimedia Files:
1. **Multi-Region Object Storage Origin:** Mezzanine video and audio master files are uploaded to cloud object storage (e.g., Amazon S3). S3 provides high durability (99.999999999%) and cross-region replication.
2. **Content Delivery Network (CDN) Edge Caching:** A global CDN (e.g., Amazon CloudFront, Akamai) caches video segments at hundreds of **Edge Locations (Points of Presence - PoPs)** distributed globally.
3. **Anycast DNS Routing & Origin Shielding:** When a user requests a video, Anycast routing directs the request to the topologically closest edge cache. If cached, content is served with minimal network latency (< 20ms). Uncached segments are fetched through an intermediate Origin Shield cache to protect origin storage.

### 2. Cloud Media Transcoding:
Raw video files are uncompressed and too large for direct consumer streaming. Cloud transcoding services (e.g., AWS Elemental MediaConvert, Google Transcoder API):
- Ingest raw source files and utilize elastic compute worker clusters (GPU/CPU instances) to decode and re-encode videos in parallel.
- Generate an **Adaptive Bitrate Streaming (ABR)** ladder: encoding the video into multiple resolution/bitrate profiles (e.g., 1080p @ 4.5 Mbps, 720p @ 2 Mbps, 480p @ 800 Kbps, 360p @ 400 Kbps).
- Package encoded fragments into chunked streaming protocols (**HLS** `.m3u8` playlist index and MPEG-DASH `.mpd` manifest).

<br>

## 🔥 Q7(b) [2 points] Write about the advantages of two main streaming protocols present in multimedia cloud.

**Answer:**

### 1. HLS (HTTP Live Streaming - Apple Standard):
- **Universal Device Compatibility:** Natively supported on iOS, macOS, Android, smart TVs, and all modern web browsers via HTML5 video extensions.
- **Standard HTTP & CDN Caching:** Because HLS segments video into standard HTTP chunks (`.ts` or `.m4s`), traffic flows through standard port 80/443 firewalls and is natively cached across existing global CDN edge servers without requiring specialized streaming servers.

### 2. MPEG-DASH (Dynamic Adaptive Streaming over HTTP):
- **International ISO Standard & Vendor Neutrality:** Unlike Apple's proprietary HLS, MPEG-DASH is an open international standard supported across heterogeneous platforms.
- **Codec Independence:** Supports arbitrary modern video and audio codecs (H.264, HEVC/H.265, AV1, VP9) and dynamic multi-language audio track selection.

<br>

## 🔥 Q8(a) [2 points] Write about the main features of Docker Containers.

**Answer:**

1. **OS-Level Virtualization via Linux Namespaces & Cgroups:** Containers share the host operating system kernel while isolating process IDs (`pid`), networking (`net`), filesystem mounts (`mnt`), and restricting CPU/RAM usage (`cgroups`).
2. **Layered Copy-on-Write Filesystem (UnionFS):** Docker images consist of read-only stacked filesystem layers. Running containers add only a thin writable top layer, enabling lightweight storage footprints and fast image sharing.
3. **Portability ("Build Once, Run Anywhere"):** Packages application binaries, libraries, and configurations together, ensuring identical execution across developer laptops, test staging, and cloud production environments.
4. **Millisecond Boot Latency:** Because containers do not boot a full guest operating system, they start almost instantaneously compared to virtual machines.

<br>

## 🔥 Q8(b) [4 points] You have an web application written in Python. Write a Dockerfile and create a docker image from the Dockerfile. Write the commands needed.

**Answer:**

### Complete Dockerfile:
```dockerfile
# 1. Base official Python runtime
FROM python:3.11-slim

# 2. Environment variables to optimize Python execution
ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1

# 3. Set working directory inside container
WORKDIR /app

# 4. Copy and install dependencies first (leverages layer caching)
COPY requirements.txt /app/
RUN pip install --no-cache-dir -r requirements.txt

# 5. Copy application source code
COPY . /app/

# 6. Expose the port the web app listens on
EXPOSE 8080

# 7. Start the application using a production WSGI server
CMD ["gunicorn", "--bind", "0.0.0.0:8080", "--workers", "2", "app:application"]
```

### Terminal Commands to Build and Run the Docker Image:
```bash
# Step 1: Build the Docker image tagged as 'python-web-app:v1'
docker build -t python-web-app:v1 .

# Step 2: Verify the newly created image is present locally
docker images

# Step 3: Run the container in detached mode mapping host port 8080 to container port 8080
docker run -d -p 8080:8080 --name my-running-web-app python-web-app:v1

# Step 4: Verify the running container status and check logs
docker ps
docker logs my-running-web-app
```

<br>

## 🔥 Q9(a) [3 points] How can two docker containers communicate with each other? Explain.

**Answer:**

Two Docker containers communicate with each other using **Docker Bridge Networks**:

```
[Host Machine]
       |
+--------------------------------------+
| User-Defined Bridge: "my-net"        |
| IP Subnet: 172.20.0.0/16             |
+--------------------------------------+
       |                        |
       v                        v
+--------------------+   +--------------------+
| Container: "web"   |   | Container: "db"    |
| IP: 172.20.0.2     |   | IP: 172.20.0.3     |
| Talks to "db:5432" |-->| Listens on 5432    |
+--------------------+   +--------------------+
```

1. **User-Defined Bridge Network:** When containers are attached to a user-defined bridge network, Docker automatically provides **Automatic Service Discovery via an Embedded DNS Server**.
2. **Name-Based Resolution:** Containers do not need hardcoded IP addresses. Container `web` can connect directly to container `db` by using its container name as a hostname: `db:5432`. Docker's internal DNS daemon (`127.0.0.11`) resolves `db` to its active internal IP.
3. **Port Isolation:** Containers on the same bridge network communicate directly across all ports without needing host port publication (`-p`). External traffic is blocked unless ports are explicitly exposed to the host.

<br>

## 🔥 Q9(b) [3 points] What are the pods and deployments in Kubernetes? How do they work together?

**Answer:**

### 1. Pods:
A **Pod** is the smallest and most fundamental deployable execution unit in Kubernetes. A Pod encapsulates one or more tightly-coupled containers (e.g., an application container and a logging sidecar) that share the same network namespace (single IP address and localhost port space) and storage volumes. Pods are ephemeral; if a Pod dies, it is not recreated automatically.

### 2. Deployments:
A **Deployment** is a declarative controller that manages the lifecycle of Pods. You describe the *desired state* in a YAML manifest (e.g., running 3 replicas of an image). The Deployment automatically manages an underlying **ReplicaSet**, continuously comparing the cluster's actual state to the desired state. Deployments provide automated self-healing, zero-downtime rolling updates, and rollbacks.

### How They Work Together:
In production, developers **never deploy naked Pods**. Instead, they define a **Deployment**. The Deployment controller creates a ReplicaSet, which launches and supervises the specified number of Pods. If a worker node crashes, the Deployment immediately creates identical replacement Pods on surviving healthy nodes, guaranteeing application availability.

<br>

## 🔥 Q10(a) [3 points] How micro-services are deployed in cloud computing? Explain.

**Answer:**

Microservices are deployed in cloud computing using containerized and serverless deployment architectures:

1. **Containerized Deployment on Kubernetes / AWS ECS:** Each microservice is packaged as an independent Docker container image. Services are deployed as Kubernetes Deployments across elastic worker node clusters, isolated in dedicated namespaces with resource CPU/RAM limits.
2. **API Gateway Pattern:** External client traffic routes through a centralized cloud API Gateway (e.g., AWS API Gateway, Kong). The gateway handles SSL termination, OAuth token validation, request routing to internal microservices, and rate limiting.
3. **Service Mesh (Istio / Envoy):** Internal service-to-service communication is governed by a service mesh sidecar proxy. The mesh transparently enforces mutual TLS (mTLS) encryption, handles dynamic traffic routing, and provides distributed tracing (Jaeger).
4. **Serverless Microservices (AWS Lambda / Google Cloud Run):** Individual microservice endpoints execute as event-driven functions that automatically scale from zero to thousands of concurrent instances on demand.

<br>

## 🔥 Q10(b) [3 points] How do we benchmark a cloud application? Explain the steps.

**Answer:**

Benchmarking a cloud application involves subjecting the system to controlled synthetic workloads to evaluate throughput, latency, and resource limits. The systematic process follows these steps:

1. **Define Objectives & SLOs:** Establish target metrics: maximum acceptable P99 response time (e.g., < 200ms), target throughput (e.g., 5,000 RPS), and workload traffic profile (read vs write ratios).
2. **Setup Isolated Mirror Environment:** Deploy a dedicated staging environment mirroring production hardware, database engines, and network topologies.
3. **Generate Synthetic Workloads:** Utilize distributed load-testing tools (e.g., **Apache JMeter, Locust, wrk**) to generate concurrent virtual users with stepped load profiles (ramp-up, steady-state, spike testing).
4. **Collect Metrics & Telemetry:** Continuously monitor multi-tier performance using cloud monitoring tools (Amazon CloudWatch, Prometheus): measuring CPU usage, memory saturation, database IOPS, and network egress.
5. **Identify Bottlenecks:** Profile slow SQL queries, database connection pool exhaustion, memory leaks, and CPU throttling.
6. **Apply System Tuning:** Add database indexes, configure Redis caching, increase worker threads, and optimize Auto Scaling thresholds.
7. **Verify & Validate:** Re-run the benchmark to confirm performance improvements and guarantee SLA compliance.

<br>


<br>


# 🐦‍🔥 END SEMESTER EXAMINATION 2025

---

<br>

## 🔥 Q1(a) [4 points] You need to build a web application for a multi-user event management system. How would you develop this application using Django?

**Answer:**

Developing a multi-user event management system using Django leverages its built-in **Model-Template-View (MTV)** architecture and batteries-included security features:

### 1. Data Modeling (`models.py`):
Define relational data entities representing events, organizers, ticket categories, and user registrations:
```python
from django.db import models
from django.contrib.auth.models import User

class Event(models.Model):
    organizer = models.ForeignKey(User, on_delete=models.CASCADE, related_name='events')
    title = models.CharField(max_length=200)
    description = models.TextField()
    start_time = models.DateTimeField()
    end_time = models.DateTimeField()
    capacity = models.PositiveIntegerField()
    banner = models.ImageField(upload_to='event_banners/')

class TicketRegistration(models.Model):
    event = models.ForeignKey(Event, on_delete=models.CASCADE, related_name='registrations')
    attendee = models.ForeignKey(User, on_delete=models.CASCADE)
    registration_date = models.DateTimeField(auto_now_add=True)

    class Meta:
        unique_together = ('event', 'attendee') # Prevent duplicate registrations
```

### 2. Business Logic & Transactional Views (`views.py`):
Handle ticket registration with strict database transaction isolation to prevent overselling:
```python
from django.shortcuts import render, get_object_or_404, redirect
from django.contrib.auth.decorators import login_required
from django.db import transaction
from .models import Event, TicketRegistration

@login_required
def book_ticket(request, event_id):
    event = get_object_or_404(Event, id=event_id)
    if request.method == 'POST':
        with transaction.atomic():
            # Lock row using select_for_update to handle race conditions
            locked_event = Event.objects.select_for_update().get(id=event_id)
            current_bookings = locked_event.registrations.count()
            if current_bookings < locked_event.capacity:
                TicketRegistration.objects.create(event=locked_event, attendee=request.user)
                return redirect('event_success')
            else:
                return render(request, 'sold_out.html', {'event': locked_event})
    return render(request, 'book_ticket.html', {'event': event})
```

### 3. Template Presentation Layer (`templates/`):
Django template engine renders dynamic event listings and dashboards using template tags (`{% for event in events %}`).

### 4. Cloud Architecture Integration:
- **Relational Metadata:** Deployed on **Amazon RDS PostgreSQL** (Multi-AZ) for ACID transactional consistency.
- **Media Storage:** Event banners uploaded directly to **Amazon S3** via `django-storages`.
- **Caching & Sessions:** User login sessions and hot trending events cached in **Amazon ElastiCache Redis**.

<br>

## 🔥 Q1(b) [2 points] Service integration is an essential component in the design of Platform-as-a-Service (PaaS) solutions. Explain.

**Answer:**

In Platform-as-a-Service (PaaS) environments (e.g., AWS Elastic Beanstalk, Google App Engine, Heroku), the underlying compute nodes and container instances are **stateless and ephemeral**: they can be terminated, recycled, or scaled out elastically at any time.

Consequently, PaaS applications cannot store persistent data on local filesystems or run internal database daemons on the application container. **Service integration** is essential because:
1. **Managed Data Persistence:** Applications must integrate with external managed persistence services (e.g., Amazon RDS, DynamoDB, Amazon S3) via environment variables and standard connection URIs.
2. **Decoupled Enterprise Capabilities:** Critical capabilities such as distributed caching (Redis/Memcached), message queuing (RabbitMQ, SQS), identity authentication (OAuth 2.0/SAML), and centralized logging (CloudWatch, Datadog) must be integrated as loosely-coupled managed services.

<br>

## 🔥 Q2(a) [4 points] Fill in the blanks. Given a collection of documents, we implement a MapReduce solution to count the frequency of each word across all documents. The functions will be called in the following sequence: map_phase() -> shuffle_sort() -> reduce_phase()

```python
def map_phase(doc):
    words = doc.split()
    return [(word, 1) for word in words]

def reduce_phase(grouped_data):
    word, counts = grouped_data
    return (word, sum(counts))

def shuffle_sort(mapped_data):
    grouped_data = __(a)__
    for __(b)__ in mapped_data:
        __(c)__
    return __(d)__
```

**Answer:**

The complete, filled-in `shuffle_sort` function implementation is:

- **(a)** `defaultdict(list)` *(or `{}`)*
- **(b)** `word, count` *(or `item`)*
- **(c)** `grouped_data[word].append(count)` *(or `grouped_data.setdefault(word, []).append(count)`)*
- **(d)** `list(grouped_data.items())` *(or `grouped_data.items()`)*

### Complete Verified Implementation:
```python
from collections import defaultdict

def shuffle_sort(mapped_data):
    grouped_data = defaultdict(list)           # Blank (a)
    for word, count in mapped_data:            # Blank (b)
        grouped_data[word].append(count)       # Blank (c)
    return list(grouped_data.items())          # Blank (d)
```

<br>

## 🔥 Q2(b) [2 points] Is random read and write access allowed in HBase? Explain.

**Answer:**

**YES, random read and write access is fully allowed and supported in Apache HBase.**

### Explanation:
HBase is designed as a distributed, column-oriented NoSQL database running on top of HDFS:
- **Random Writes:** When a write arrives, HBase appends it to a durable Write-Ahead Log (WAL) on HDFS and stores the record in an in-memory sorted buffer called **MemStore**. Once in MemStore, the write is immediately acknowledged to the client (sub-millisecond latency). When full, MemStore flushes sequentially to disk as an immutable **HFile**.
- **Random Reads:** To retrieve a record by its `RowKey`, HBase checks the in-memory **MemStore**, the in-memory **BlockCache**, and utilizes **Bloom Filters** to identify the exact HFile block containing the key, bypassing full-table scans. This delivers point lookups in 1 to 5 milliseconds across billions of rows.

<br>

## 🔥 Q3(a) [3 points] Explain the differences between the ResourceManager and the NodeManager in a YARN-based Hadoop cluster.

**Answer:**

| 🌟 Feature | ResourceManager (RM) | NodeManager (NM) |
| :--- | :--- | :--- |
| **Architectural Scope** | Global master authority for the entire cluster. | Local slave daemon running on a single physical node. |
| **Primary Responsibility** | Arbitrates and allocates cluster compute resources (CPU vCores, RAM) among all competing applications. | Manages the lifecycles of local containers and monitors node hardware health. |
| **Internal Components** | Contains the **Scheduler** (pluggable resource allocator) and **ApplicationsManager** (manages AM lifecycle). | Launches container processes, monitors resource limits, and runs container health checks. |
| **Heartbeat Role** | Receives periodic heartbeats and node status updates from all NodeManagers. | Transmits periodic heartbeats containing CPU/memory utilization and active container status to the RM. |
| **Instance Count** | One active per cluster (with an optional standby for HA). | One instance per physical worker machine in the cluster. |

<br>

## 🔥 Q3(b) [3 points] You have n cloud tasks, and each task i has a reward that reflects how much it benefits from being allocated to a resource. Your objective is to maximize the total reward by choosing a set of tasks to allocate, subject to the constraint that no two consecutive tasks can be allocated to the same resource. Write an algorithm to solve this problem.

**Answer:**

### Algorithm Analysis:
This optimization problem is formulated using **Dynamic Programming**. For each task $i$, we decide between:
1. **Excluding Task $i$:** The optimal reward is $DP[i-1]$.
2. **Including Task $i$:** We receive reward $R[i]$ plus the optimal reward from non-consecutive tasks up to $i-2$, i.e., $R[i] + DP[i-2]$.

Recurrence:
$$\mathbf{DP[i] = \max\left(DP[i-1],\, R[i] + DP[i-2]ight)}$$

### Python Algorithm (O(n) Time, O(1) Space):
```python
def maximize_task_reward(rewards: list[int]) -> int:
    """
    Computes maximum reward without allocating two consecutive tasks.
    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    if not rewards:
        return 0
    n = len(rewards)
    if n == 1:
        return rewards[0]

    # prev2 stores DP[i-2], prev1 stores DP[i-1]
    prev2 = rewards[0]
    prev1 = max(rewards[0], rewards[1])

    for i in range(2, n):
        current = max(prev1, rewards[i] + prev2)
        prev2 = prev1
        prev1 = current

    return prev1

# Example Test Case:
# rewards = [10, 25, 30, 15, 40]
# Result: 80 (choosing tasks 0, 2, and 4: 10 + 30 + 40 = 80)
```

<br>

## 🔥 Q4(a) [4 points] Write HiveQL statement to find the average salary of employees in each department, but only for employees whose salary is greater than the average salary for their own department.

**Answer:**

### HiveQL Query (Using Window Analytic Function & Subquery):
```sql
SELECT 
    dept,
    AVG(salary) AS avg_salary_above_dept_mean
FROM (
    SELECT 
        id,
        name,
        dept,
        salary,
        AVG(salary) OVER (PARTITION BY dept) AS dept_avg_salary
    FROM employee
) subquery
WHERE salary > dept_avg_salary
GROUP BY dept;
```

### Alternative HiveQL Query (Using Correlated Join with Group By):
```sql
SELECT 
    e.dept,
    AVG(e.salary) AS avg_salary_above_dept_mean
FROM employee e
JOIN (
    SELECT dept, AVG(salary) AS dept_avg
    FROM employee
    GROUP BY dept
) d_avg 
ON e.dept = d_avg.dept
WHERE e.salary > d_avg.dept_avg
GROUP BY e.dept;
```

<br>

## 🔥 Q4(b) [2 points] Can Pig Execution Engine execute the Pig Latin scripts by compiling them into MapReduce jobs?

**Answer:**

**YES, absolutely.** 

### Technical Explanation:
The primary execution mode of Apache Pig is its **MapReduce Mode** (`pig -x mapreduce`). 
1. When a user submits a Pig Latin script, the Pig compiler builds a logical plan of dataflow transformations (`FILTER`, `GROUP`, `JOIN`).
2. An optimization pass reorganizes the DAG (e.g., pushing projection and filter operations earlier).
3. The **Pig Execution Engine** compiles the physical plan into one or more native Java **Hadoop MapReduce jobs**.
4. These jobs are packaged into JAR files, submitted to Hadoop YARN, and executed in parallel across the cluster reading and writing data to HDFS.

<br>

## 🔥 Q5(a) [3 points] How does Spark Streaming ensure fault tolerance? Explain.

**Answer:**

Spark Streaming achieves end-to-end fault tolerance through four complementary mechanisms:

1. **Deterministic Lineage Recomputation:** In Spark's micro-batch model (DStreams), data is discretized into a continuous sequence of immutable RDDs. If a worker node crashes and loses an in-memory RDD partition, Spark recomputes that specific missing partition using the RDD's deterministic DAG lineage without physical data replication.
2. **Write-Ahead Logs (WAL):** When streaming receivers ingest raw data from external message queues (e.g., Kafka, Flume), data is simultaneously written synchronously to a durable Write-Ahead Log in HDFS or S3. If a node fails before processing buffered data, the newly spawned executor recovers the uncommitted data from the WAL.
3. **Reliable Receivers with Acknowledgments:** Receivers acknowledge message receipt back to sources (like Kafka) only after data is durably replicated across nodes or committed to WAL.
4. **State Checkpointing:** For stateful streaming transformations (such as windowed aggregations or `updateStateByKey`), Spark periodically serializes the state RDDs and metadata to durable HDFS storage.

<br>

## 🔥 Q5(b) [3 points] How is the data integrity managed in cloud computing? Give an example.

**Answer:**

Data integrity ensures that data remains uncorrupted, unaltered, and protected against unauthorized tampering during transmission, processing, and storage.

### Integrity Management Mechanisms:
1. **Cryptographic Checksums & Hashing:** Generating one-way cryptographic hash digests (e.g., SHA-256, MD5) upon data generation and verifying the hash upon retrieval.
2. **Message Authentication Codes (HMAC):** Using shared secret keys to guarantee that data in transit has not been tampered with by an active attacker.
3. **Database Constraints & ACID Transactions:** Enforcing entity integrity, referential foreign keys, and atomic commits.

### Concrete Example: Amazon S3 Content-MD5 / ETag Verification:
When a client uploads an object to Amazon S3 using the Boto3 SDK, the client computes the MD5/SHA-256 hash of the file payload and transmits it in the `Content-MD5` HTTP header. Amazon S3 receives the binary stream, independently computes the hash, and compares it against the client-provided digest. If even a single byte differs (due to packet corruption or network bit-flips), S3 rejects the upload with an `InvalidDigest` error and forces a retransmission.

<br>

## 🔥 Q6(a) [3 points] In Security Assertion Markup Language (SAML) based authentication, who performs the user authentication? Explain with an example.

**Answer:**

In SAML-based authentication, the **Identity Provider (IdP)** performs the user authentication.

### Explanation:
- The **Service Provider (SP)** (e.g., Salesforce, AWS Management Console, Google Workspace) never prompts for, receives, or validates the user's password. It delegates authentication entirely to the Identity Provider.
- The **Identity Provider (IdP)** (e.g., Okta, Microsoft Entra ID / Azure AD, Ping Identity) hosts the authoritative corporate user directory (Active Directory/LDAP), prompts the user for login credentials and MFA tokens, and validates their identity.

### Concrete Example:
Suppose an employee at a corporation attempts to log into the company's AWS Cloud Console (Service Provider). 
1. The AWS Console redirects the employee's browser to **Okta** (the enterprise Identity Provider).
2. **Okta** presents the login screen, authenticates the employee's username, password, and Duo MFA push notification.
3. Once authenticated, **Okta** signs an XML SAML assertion token certifying the employee's identity and roles (`Role: CloudAdmin`), and redirects the browser back to AWS.
4. AWS verifies Okta's cryptographic signature and admits the employee into the console.

<br>

## 🔥 Q6(b) [3 points] Can Digital Signatures guarantee confidentiality? Justify.

**Answer:**

**NO, Digital Signatures CANNOT guarantee confidentiality.**

### Technical Justification:
1. **Purpose of Digital Signatures:** A digital signature is created by computing a cryptographic hash of a plaintext message ($H = 	ext{SHA-256}(M)$) and encrypting only that hash using the sender's **Private Key** ($S = E_{K_{priv}}(H)$).
2. **Plaintext Transmission:** The generated signature $S$ is transmitted across the network **alongside the original, unencrypted plaintext message $M$**.
3. **What Digital Signatures Provide:**
   - *Authenticity:* Proves who sent the message (verified using sender's public key).
   - *Integrity:* Proves the message was not modified in transit.
   - *Non-Repudiation:* Sender cannot deny sending the message.
4. **Why Confidentiality Fails:** Because the message body $M$ is transmitted in unencrypted plaintext, any passive eavesdropper intercepting the packet on the network wire can read the message contents directly. To achieve confidentiality, the plaintext message must be encrypted using symmetric/asymmetric encryption (forming a **Digital Envelope**).

<br>

## 🔥 Q7(a) [3 points] How Message Authentication Code prevents Data Tampering? Explain with an example.

**Answer:**

A Message Authentication Code (MAC or HMAC) is a cryptographic checksum generated using a shared symmetric secret key $K$ and the message $M$:
$$\mathbf{	ext{MAC} = 	ext{HMAC}(K,\, M)}$$

### How it Prevents Tampering:
1. **Shared Secret Requirement:** Computing a valid MAC requires possession of the secret key $K$, which is known only to the legitimate sender and receiver.
2. **Tamper Detection:** If an attacker intercepts the transmission and alters the message content from $M$ to $M'$ (tampering), the attacker cannot generate the corresponding valid $	ext{MAC}' = 	ext{HMAC}(K, M')$ without knowing secret key $K$.
3. When the receiver calculates $	ext{HMAC}(K, M')$ using their secret key, the value will not match the transmitted MAC. The receiver immediately detects tampering and discards the packet.

### Concrete Example:
Consider a cloud banking API transferring funds:
- Plaintext Message: `Transfer $500 from Acc_A to Acc_B`
- Shared Key: `SecretKey987`
- Sender transmits: `Message` + `MAC: 4a8f9c...`
- Attacker alters message to: `Transfer $50,000 from Acc_A to Acc_B`
- When the cloud server recomputes the HMAC of the altered message with `SecretKey987`, the resulting digest is `e2b17a...`, which does not match `4a8f9c...`. The fraudulent transfer is aborted immediately.

<br>

## 🔥 Q7(b) [3 points] How can we implement K-Nearest Neighbors Algorithm using Map Reduce? Write map and reduce functions.

**Answer:**

The K-Nearest Neighbors (KNN) algorithm classifies an unlabeled query point $\mathbf{q}$ by finding the $k$ closest labeled training samples from a distributed dataset.

### Map Function:
The Mapper reads training instances $(\mathbf{x}_i, 	ext{label}_i)$, computes the Euclidean distance between $\mathbf{x}_i$ and the broadcast query point $\mathbf{q}$, and emits all distances under a single common key.

```python
import math

QUERY_POINT = [2.5, 4.0, 1.2]  # Broadcast test query point

def knn_mapper(training_sample):
    """
    Input: training_sample = (features_list, label)
    Emits: (1, (distance, label))
    """
    features, label = training_sample
    # Compute Euclidean Distance
    distance = math.sqrt(sum((f - q) ** 2 for f, q in zip(features, QUERY_POINT)))
    # Emit dummy key 1 to channel all distances to the Reducer
    return (1, (distance, label))
```

### Reduce Function:
The Reducer collects all `(distance, label)` pairs, sorts them in ascending order of distance, selects the top-$k$ nearest instances, and performs majority voting to output the predicted class label.

```python
from collections import Counter

K = 5  # Number of nearest neighbors

def knn_reducer(key, distance_label_pairs):
    """
    Input: distance_label_pairs = [(dist1, label1), (dist2, label2), ...]
    Emits: (QUERY_POINT, predicted_class)
    """
    # Sort pairs by distance ascending
    distance_label_pairs.sort(key=lambda x: x[0])
    
    # Extract labels of top-k nearest neighbors
    top_k_labels = [label for dist, label in distance_label_pairs[:K]]
    
    # Majority voting
    predicted_class = Counter(top_k_labels).most_common(1)[0][0]
    
    return (tuple(QUERY_POINT), predicted_class)
```

<br>

## 🔥 Q8(a) [4 points] Explain how Multimedia Cloud Infrastructure can perform Video Encoding and Media Analytics.

**Answer:**

### 1. Video Encoding in Multimedia Cloud:
- **Distributed Chunk Encoding:** Raw mezzanine master video files (e.g., ProRes 4K) stored in object storage (Amazon S3) are partitioned into short temporal segments.
- **Elastic Transcoding Farms:** Transcoding compute clusters (e.g., AWS Elemental MediaConvert, auto-scaled GPU EC2 worker nodes) encode these segments concurrently into an **Adaptive Bitrate (ABR)** ladder (1080p, 720p, 480p, 360p at varying bitrates).
- **HLS/DASH Packaging:** Encoded fragments are packaged into chunked container formats (`.m4s` / `.ts`) along with master manifest playlist files (`.m3u8` / `.mpd`) and pushed to CDN edge caches.

### 2. Media Analytics in Multimedia Cloud:
- **Automated Computer Vision & Object Recognition:** Serverless video processing pipelines extract video keyframes and submit them to deep learning APIs (e.g., AWS Rekognition) to identify faces, athletes, brand logos, and explicit content.
- **Audio Speech-to-Text & Translation:** Audio streams are parsed through speech recognition models (e.g., AWS Transcribe) to generate automated multi-lingual closed captions and searchable subtitle transcripts.
- **Viewer Telemetry Analytics:** CDN edge logs capture real-time player buffer underruns, bitrate switching events, and viewer drop-off timestamps, feeding Kinesis and Spark pipelines to optimize video encoding ladders.

<br>

## 🔥 Q8(b) [2 points] What mechanisms are used to ensure low latency during live streaming?

**Answer:**

1. **Chunked Media Application Format (CMAF) Chunked Transfer-Encoding:** Traditional HLS downloads entire 6-second segments before playing. CMAF breaks video segments into tiny 200ms chunks; web servers stream these fragments to players via HTTP/1.1 chunked transfer encoding as they are being encoded, reducing broadcast delay to 1-2 seconds.
2. **Low-Latency HLS (LL-HLS) & LL-DASH:** Utilizes partial video segment generation and HTTP/2 multiplexed push updates to minimize round-trip playlist polling delays.
3. **WebRTC for Ultra-Low Latency (< 500ms):** Uses UDP-based Real-Time Transport Protocol (RTP) with selective retransmission, eliminating TCP head-of-line blocking for interactive use cases (sports betting, live gaming auctions).

<br>

## 🔥 Q9(a) [3 points] Write a Dockerfile for a python application. Assume that the python application will run in port 8080.

**Answer:**

```dockerfile
# Step 1: Minimal official Python runtime
FROM python:3.11-slim

# Step 2: Prevent Python from buffering standard output and writing .pyc files
ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1

# Step 3: Set working directory inside container
WORKDIR /app

# Step 4: Copy and install Python dependencies first to utilize Docker layer cache
COPY requirements.txt /app/
RUN pip install --no-cache-dir -r requirements.txt

# Step 5: Copy application source code
COPY . /app/

# Step 6: Document listening port
EXPOSE 8080

# Step 7: Define startup command
CMD ["python", "app.py"]
```

<br>

## 🔥 Q9(b) [3 points] We want to run a container for a Python app, and another container for a Redis database. Both containers need to communicate with each other. Write Docker commands to create a bridge network to enable this communication.

**Answer:**

```bash
# Step 1: Create a custom user-defined bridge network
docker network create --driver bridge my-app-network

# Step 2: Run the Redis container on the custom bridge network
# Specifying '--name redis-db' registers the container with Docker's internal DNS
docker run -d --name redis-db --network my-app-network redis:7-alpine

# Step 3: Run the Python application container on the same bridge network
# In the Python application code, configure Redis connection to: "redis://redis-db:6379"
docker run -d --name python-app --network my-app-network -p 8080:8080 my-python-app:v1

# Step 4: Verify DNS resolution and inter-container network connectivity
docker exec -it python-app ping -c 2 redis-db
```

<br>

## 🔥 Q10(a) [3 points] Communication between services over a network can introduce latency compared to monolithic architectures. Justify.

**Answer:**

In a monolithic architecture, communication between components occurs via **in-process function calls** in local CPU memory registers, executing in less than **10 to 50 nanoseconds**.

In a microservices architecture, every service boundary crossing requires network transit, introducing significant latency due to:
1. **Network Serialization & Deserialization:** Transforming native objects into JSON or Protocol Buffer byte streams and parsing them back at the destination consumes CPU cycles.
2. **Transport Handshakes & Protocol Overhead:** Establishing TCP connections, negotiating TLS 1.3 encryption handshakes, and handling HTTP headers introduce substantial round-trip delays (RTT).
3. **Physical Network Transit & Routing:** Packets must traverse virtual network interfaces (vNICs), virtual switches, physical routers, and cabling, introducing **1 to 5 milliseconds** of latency per hop.
4. **Cascading Network Calls (Fanout Amplification):** A single user request may trigger a synchronous chain of 5 to 10 downstream REST calls, multiplying total latency.

<br>

## 🔥 Q10(b) [3 points] Why do Microservices need a Message Broker for communication?

**Answer:**

Microservices rely on Message Brokers (e.g., Apache Kafka, RabbitMQ, Amazon SQS) to implement **asynchronous, event-driven communication**, addressing critical limitations of synchronous REST calls:

1. **Temporal & Architectural Decoupling:** The producing service sends an event and immediately resumes execution without blocking. Services operate independently of each other's availability.
2. **Traffic Spike Buffering (Load Leveling):** Brokers absorb sudden incoming request spikes (e.g., 20,000 orders/sec during flash sales) into durable queues. Downstream services process messages at their own sustainable rate without crashing.
3. **Fault Isolation & Resilience:** If a downstream consumer (e.g., Notification Service) experiences an outage, the producer continues operating smoothly. Messages wait safely in the queue until the consumer recovers.
4. **Publish-Subscribe (Pub/Sub) Fanout:** A single event (e.g., `OrderPlaced`) is simultaneously delivered to multiple independent subscribers (Payment, Inventory, Analytics, Shipping) without the producer having any knowledge of downstream consumers.

<br>


<br>
# 🐦‍🔥 TOP 25 FOUNDATIONAL PRE-MIDSEM EXAMINATION QUESTIONS & MODEL ANSWERS

---

<br>

## 🔥 Q1. Define Cloud Computing according to NIST. Explain its five essential characteristics.

**Answer:**

### NIST Formal Definition:
According to the National Institute of Standards and Technology (NIST):
> *"Cloud computing is a model for enabling ubiquitous, convenient, on-demand network access to a shared pool of configurable computing resources (e.g., networks, servers, storage, applications, and services) that can be rapidly provisioned and released with minimal management effort or service provider interaction."*

### Five Essential Characteristics:
1. **On-Demand Self-Service:** Consumers can provision computing capabilities (such as server compute time and network storage) automatically as needed, without requiring human intervention from the service provider.
2. **Broad Network Access:** Capabilities are available over the standard network and accessed through standard mechanisms that promote use by heterogeneous thin or thick client platforms (mobile phones, tablets, laptops, workstations).
3. **Resource Pooling:** The provider's computing resources are pooled to serve multiple consumers using a multi-tenant model, with physical and virtual resources dynamically assigned and reassigned according to consumer demand. The customer has no exact knowledge of the physical location of resources (location independence).
4. **Rapid Elasticity:** Capabilities can be elastically provisioned and released—in some cases automatically—to scale rapidly outward and inward commensurate with demand. To the consumer, available resources often appear infinite and can be appropriated in any quantity at any time.
5. **Measured Service:** Cloud systems automatically control and optimize resource use by leveraging a metering capability at some level of abstraction appropriate to the type of service (e.g., storage, processing, bandwidth, active user accounts). Resource usage can be monitored, controlled, and reported, providing transparency for both the provider and consumer.

<br>

## 🔥 Q2. Compare IaaS, PaaS, and SaaS service models with respect to architecture and the Shared Responsibility Model.

**Answer:**

| Architectural Layer | Traditional On-Premise | Infrastructure as a Service (IaaS) | Platform as a Service (PaaS) | Software as a Service (SaaS) |
| :--- | :--- | :--- | :--- | :--- |
| **Applications** | Customer Manages | Customer Manages | Customer Manages | **Cloud Provider Manages** |
| **Data & Metadata** | Customer Manages | Customer Manages | Customer Manages | **Cloud Provider Manages** |
| **Runtime Environment** | Customer Manages | Customer Manages | **Cloud Provider Manages** | **Cloud Provider Manages** |
| **Middleware** | Customer Manages | Customer Manages | **Cloud Provider Manages** | **Cloud Provider Manages** |
| **Operating System** | Customer Manages | Customer Manages | **Cloud Provider Manages** | **Cloud Provider Manages** |
| **Virtualization** | Customer Manages | **Cloud Provider Manages** | **Cloud Provider Manages** | **Cloud Provider Manages** |
| **Physical Servers** | Customer Manages | **Cloud Provider Manages** | **Cloud Provider Manages** | **Cloud Provider Manages** |
| **Storage Subsystems** | Customer Manages | **Cloud Provider Manages** | **Cloud Provider Manages** | **Cloud Provider Manages** |
| **Networking Hardware** | Customer Manages | **Cloud Provider Manages** | **Cloud Provider Manages** | **Cloud Provider Manages** |
| **Primary Real-World Examples** | Private Corporate Data Center | Amazon EC2, GCE, Azure VMs | AWS Elastic Beanstalk, Heroku, Google App Engine | Google Workspace, Salesforce, Microsoft 365 |

<br>

## 🔥 Q3. Differentiate between Public, Private, Hybrid, and Community Cloud deployment models.

**Answer:**

| Characteristic | Public Cloud | Private Cloud | Hybrid Cloud | Community Cloud |
| :--- | :--- | :--- | :--- | :--- |
| **Ownership & Governance** | Third-party cloud service provider (AWS, Microsoft, Google). | Single enterprise organization or dedicated third party. | Combined ownership across public provider and private enterprise. | Shared collaboratively by multiple organizations with common goals. |
| **Infrastructure Location** | Off-premises at provider multi-tenant data centers. | On-premises at corporate facility or hosted privately. | Distributed across private data centers and public cloud zones. | On-premise or hosted by a third-party specialized provider. |
| **Data Security & Privacy** | Standard multi-tenant logical isolation. | Maximum security; physical and dedicated boundary isolation. | Critical data retained in private tier; non-sensitive compute in public tier. | High; restricted to participating authenticated community entities. |
| **Cost Model** | Operational Expenditure (OpEx); zero capital expenditure. | High Capital Expenditure (CapEx) for hardware plus ongoing OpEx. | Balanced hybrid expenditure profile. | Shared capital and operational expenses across participants. |
| **Target Workload** | Variable, public-facing applications; startups; general computing. | Mission-critical financial, defense, healthcare databases. | Cloud-bursting workloads; disaster recovery replication. | Joint government agencies, scientific consortia, regional banks. |

<br>

## 🔥 Q4. What is Virtualization? Why is it considered the foundational technology of Cloud Computing?

**Answer:**

**Virtualization** is the technological process of creating a software-based (virtual) representation of physical computing resources, including central processing units, system memory, network interfaces, and persistent storage volumes.

### Foundational Role in Cloud Computing:
1. **Enabler of Multi-Tenancy:** Virtualization allows a single massive physical server to be partitioned into multiple isolated execution environments (Virtual Machines), enabling disparate customers to safely share identical hardware.
2. **Elastic Scaling & Agility:** Because virtual machines exist simply as encapsulated software containers and disk image files, they can be booted, cloned, paused, migrated, and terminated programmatically via API calls within seconds.
3. **Resource Optimization:** Consolidates multiple under-utilized physical servers onto fewer, highly-utilized physical platforms, raising server utilization from $10\%$ to over $75\%$.
4. **Abstracted Management:** Decouples software applications from underlying hardware lifecycles, enabling transparent cloud maintenance without customer downtime.

<br>

## 🔥 Q5. Explain the differences between Full Virtualization, Para-Virtualization, and Hardware-Assisted Virtualization.

**Answer:**

1. **Full Virtualization:**
   - **Mechanism:** The hypervisor provides complete architectural simulation of underlying physical hardware. The guest OS runs completely unmodified and is unaware of virtualization.
   - **Challenge:** Non-virtualizable sensitive instructions (e.g., ring-0 x86 instructions) executed by guest OS are intercepted and dynamically rewritten using **Binary Translation**.
   - **Trade-off:** High hypervisor emulation overhead; moderate performance.
2. **Para-Virtualization:**
   - **Mechanism:** The guest OS kernel is explicitly modified. Non-virtualizable sensitive hardware instructions are replaced at compile-time with **Hypercalls** that invoke the hypervisor directly.
   - **Trade-off:** Delivers superior I/O throughput by eliminating binary translation, but suffers from lack of operating system portability (proprietary OS like Windows cannot be modified).
3. **Hardware-Assisted Virtualization:**
   - **Mechanism:** Employs hardware-level CPU architectural enhancements (Intel VT-x, AMD-V). The CPU introduces new operational execution rings (e.g., VMX Root Mode for Hypervisor, VMX Non-Root Mode for Guest OS).
   - **Trade-off:** Guest OS runs completely unmodified with near-native hardware performance, representing the standard in modern enterprise cloud platforms.

<br>

## 🔥 Q6. Explain the difference between Horizontal Scaling (Scale-Out) and Vertical Scaling (Scale-Up) in cloud environments.

**Answer:**

| Parameter | Vertical Scaling (Scale-Up / Scale-Down) | Horizontal Scaling (Scale-Out / Scale-In) |
| :--- | :--- | :--- |
| **Operational Definition** | Adding more computing resources (RAM, CPU cores, NVMe storage) to an existing single instance. | Adding more discrete instances/nodes of identical specification into the compute pool. |
| **Hardware Architecture** | Limited by the physical capacity bounds of the underlying motherboard/server chassis. | Theoretically limitless; scales across thousands of distributed commodity servers. |
| **Service Interruption** | Often requires instance restart/downtime during instance type resizing. | Zero downtime; new instances are registered into load balancer pools transparently. |
| **Architectural Complexity** | Very simple; software architecture and database code remain unchanged. | Requires distributed stateless architectures, session externalization, and load balancing. |
| **Cost Scaling Profile** | Non-linear cost curve; extreme high-end compute instances become exponentially expensive. | Linear and cost-effective; leverages inexpensive commodity instances and spot pools. |

<br>

## 🔥 Q7. Detail the architectural differences and use cases of Object Storage, Block Storage, and File Storage.

**Answer:**

```
Object Storage (Flat):       Block Storage (Sectors):      File Storage (Hierarchy):
+---------------------+      +---------------------+      +---------------------+
| [ID] [Metadata] [Data]|    | [Sector 0] [Sector 1]|     | Root /              |
| [ID] [Metadata] [Data]|    | [Sector 2] [Sector 3]|     |   ├── docs/         |
| Key-Value Bucket    |      | Raw Block Device    |      |   └── images/       |
+---------------------+      +---------------------+      +---------------------+
```

1. **Object Storage (e.g., Amazon S3):**
   - Stores data as distinct, immutable objects inside a flat bucket namespace.
   - Objects consist of file data, customizable metadata tags, and a unique identification key.
   - Best for massive unstructured datasets, video files, backups, and machine learning training corpora.
2. **Block Storage (e.g., Amazon EBS):**
   - Exposes raw, formatted block volumes directly attached to a single virtual machine over high-speed networks.
   - Provides ultra-low latency random read/write I/O required for relational databases (PostgreSQL, MySQL, Oracle) and OS filesystems.
3. **File Storage (e.g., Amazon EFS):**
   - Exposes a standard hierarchical directory structure accessible simultaneously by hundreds of virtual instances using network file protocols (NFSv4/SMB).
   - Ideal for collaborative document sharing, enterprise application migration, and shared CMS web roots.

<br>

## 🔥 Q8. Explain the architecture of Software Defined Networking (SDN) and the role of the OpenFlow protocol.

**Answer:**

Software Defined Networking (SDN) is an architectural framework that decouples the network **Control Plane** (which decides where traffic is sent) from the underlying **Data Plane** (which forwards traffic based on control decisions):

### SDN Architectural Tiers:
1. **Application Plane:** Network applications (firewalls, IDS, QoS traffic shapers) communicate network intent to the controller via **Northbound APIs**.
2. **Control Plane:** The centralized SDN Controller maintains an end-to-end global map of the network topology, computes optimal routing graphs, and pushes forwarding rules.
3. **Data Plane:** Physical and virtual switches that inspect incoming packet headers and execute matching actions based on their internal Flow Tables.

### Role of OpenFlow Protocol:
- Operates as the standardized **Southbound Interface**.
- Populates the switch **Flow Table**, which consists of:
  - *Match Fields:* Ingress port, source/destination MAC, source/destination IP, TCP/UDP ports.
  - *Counters:* Number of matching packets and total bytes processed.
  - *Actions:* Forward to port, drop packet, push/pop VLAN tag, rewrite header, or send to controller for inspection.

<br>

## 🔥 Q9. Describe Network Function Virtualization (NFV) and explain how it complements SDN.

**Answer:**

**Network Function Virtualization (NFV)** is the architectural practice of replacing dedicated, proprietary hardware appliances (such as custom routers, firewalls, load balancers, and WAN accelerators) with software instances called **Virtualized Network Functions (VNFs)** executing on standard, high-volume commodity servers, storage, and cloud switches.

### NFV Architectural Framework (ETSI):
1. **Virtualized Network Functions (VNFs):** Software implementations of network services (e.g., virtual firewall, virtual router).
2. **NFV Infrastructure (NFVI):** Hardware resources, the virtualization layer (hypervisors), and virtual resources (vCPU, vSwitch).
3. **Management and Network Orchestration (MANO):** Orchestrates physical/virtual resources and coordinates VNF lifecycle management.

### Complementary Relationship with SDN:
- **NFV virtualizes the network functions**, eliminating hardware vendor lock-in.
- **SDN virtualizes network routing control**, dynamically programming flow paths between those virtual functions.
- *Synergy:* NFV provides the software appliances (e.g., a virtual firewall), while SDN dynamically steers network traffic through that virtual firewall via flow-table manipulation (Service Function Chaining).

<br>

## 🔥 Q10. Explain the components and operational mechanics of Service Level Agreements (SLAs) in Cloud Computing.

**Answer:**

A Cloud Service Level Agreement (SLA) is a formal contract between a cloud provider and customer delineating guaranteed service standards and financial remedies upon failure:

### Core Structural Components:
1. **Service Level Indicators (SLIs):** Specific quantitative metrics tracking system behavior in real-time (e.g., Error Rate, Request Latency, Packet Loss).
2. **Service Level Objectives (SLOs):** Contractually agreed target thresholds defined using SLIs over a set evaluation period:
   $$\text{Availability SLO} = \left( \frac{\text{Total Time} - \text{Downtime}}{\text{Total Time}} \right) \times 100 \ge 99.99\%$$
3. **Service Credits & Financial Penalties:**
   - Predefined sliding-scale billing discounts credited to the customer if the provider breaches the monthly availability commitment:
     - Availability $< 99.99\%$ but $\ge 99.0\% \rightarrow 10\%$ credit refund.
     - Availability $< 99.0\% \rightarrow 25\%$ to $100\%$ credit refund.
4. **Exclusions Clause:** Circumstances explicitly exempted from downtime calculations: client account suspension, scheduled maintenance, and internet provider outages outside the cloud provider's network perimeter.

<br>

## 🔥 Q11. Describe the MapReduce execution pipeline with an architectural diagram.

**Answer:**

MapReduce processes immense datasets through a distributed master-worker architecture:

```
[ Input Splits (S3/HDFS) ]
      |
      v
+------------------------+
|     MAP PHASE          |  Worker nodes run Map function in parallel;
| (Map Tasks 1, 2, 3...) |  generates intermediate (Key, Value) pairs
+------------------------+
      |
      v
+------------------------+
|    SHUFFLE & SORT      |  Partitions and sorts intermediate data;
| (Network Redistribution)| routes identical keys to identical Reducers
+------------------------+
      |
      v
+------------------------+
|    REDUCE PHASE        |  Combines and aggregates value lists
| (Reduce Tasks 1, 2...) |  for each discrete key
+------------------------+
      |
      v
[ Final Output Files ]
```

### Step-by-Step Pipeline Mechanics:
1. **Splitting & Assignment:** The input dataset is segmented into fixed blocks (typically 64 MB–128 MB). The master process schedules Map tasks onto nodes storing the data blocks (data locality).
2. **Map Execution:** The worker reads input pairs, executes custom transform logic, and writes intermediate key-value pairs to local memory buffers.
3. **Spilling & Partitioning:** As memory buffers fill, records are partitioned into buckets based on a hash of the key (`hash(key) mod R`) and sorted before writing to local disk.
4. **Shuffle & Sort:** Reduce workers issue remote read requests to pull their designated partitions across the network switch. Intermediate records with identical keys are merged.
5. **Reduce Execution:** The Reducer iterates over the array of values associated with each unique key, emits the aggregated result, and appends output to the distributed filesystem.

<br>

## 🔥 Q12. Explain the architecture and components of Amazon Elastic Compute Cloud (EC2).

**Answer:**

Amazon Elastic Compute Cloud (EC2) provides resizable, on-demand compute capacity in the cloud.

### Core Components:
1. **Amazon Machine Image (AMI):** Pre-configured virtual appliance templates containing the operating system, runtime libraries, and software configurations required to boot an instance.
2. **Instance Types:** Specialized hardware configurations categorized by workload profile:
   - *General Purpose (e.g., t3, m5):* Balanced compute, memory, and networking.
   - *Compute Optimized (e.g., c6g, c5):* High-performance processors for batch jobs and compute-heavy modeling.
   - *Memory Optimized (e.g., r5):* High RAM-to-vCPU ratio for in-memory caches and databases.
   - *Storage Optimized (e.g., i3):* High sequential NVMe SSD throughput for big data and NoSQL systems.
3. **Security Groups:** Stateful virtual firewalls controlling inbound and outbound network traffic at the instance level.
4. **Key Pairs:** Asymmetric cryptographic key pairs (RSA or ED25519) ensuring secure SSH (Linux) or RDP (Windows) administrative access without transmitting plain-text passwords.
5. **Elastic Block Store (EBS):** High-performance network-attached block storage devices attached as persistent boot and data drives.

<br>

## 🔥 Q13. Contrast Amazon SQS (Queuing) and Amazon SNS (Pub/Sub Notification).

**Answer:**

| Evaluation Factor | Amazon Simple Queue Service (SQS) | Amazon Simple Notification Service (SNS) |
| :--- | :--- | :--- |
| **Messaging Paradigm** | **Point-to-Point (Queue-based):** A message is pulled by and delivered to exactly one consumer. | **Publish-Subscribe (Fan-out):** A message is published to a topic and pushed simultaneously to all subscribers. |
| **Delivery Model** | **Pull-based:** Consumers continuously poll the queue (`ReceiveMessage`) to retrieve items. | **Push-based:** SNS instantly triggers and invokes subscriber endpoints. |
| **Message State Persistence** | Persists messages up to 14 days until explicitly deleted by a consumer. | Ephemeral; if an endpoint is unreachable and retries exhaust, message is lost (unless DLQ attached). |
| **Primary Use Cases** | Asynchronous batch job queuing, decoupling processing tiers, task buffering. | Real-time fan-out notifications, mobile alerts, system event broadcasting. |
| **Consumer Decoupling** | Multiple workers can compete for messages on a single queue for load balancing. | Broadcasts identical events to diverse downstream heterogenous systems simultaneously. |

<br>

## 🔥 Q14. Explain the mechanics of Content Delivery Networks (CDNs) and Amazon CloudFront.

**Answer:**

A Content Delivery Network (CDN) is a globally distributed system of proxy caching servers deployed at points of presence (Edge Locations) worldwide:

### Operational Workflow:
1. An end-user enters a URL requesting a web asset (e.g., `https://example.com/logo.png`).
2. Anycast DNS routes the user's request to the **geographically closest CloudFront Edge Location**.
3. **Cache Hit Scenario:** If the edge server already contains a fresh, unexpired copy of `logo.png` in its local SSD cache, it returns the asset directly to the user in milliseconds.
4. **Cache Miss Scenario:** If the asset is absent or its Time-to-Live (TTL) has expired:
   - The edge location forwards the request across the optimized AWS global fiber backbone to the **Origin Server** (Amazon S3 bucket, Elastic Load Balancer, or custom web host).
   - The origin returns the asset; the edge server saves it in its local cache according to caching headers (`Cache-Control: max-age=86400`) and serves it to the user.
5. Subsequent requests from any users within that metropolitan vicinity result in instantaneous cache hits.

<br>

## 🔥 Q15. Detail the components and configuration of Amazon Auto Scaling Groups.

**Answer:**

Amazon Auto Scaling Groups (ASG) ensure that the optimal number of EC2 instances are running to handle application load:

### Essential ASG Parameters:
- **Minimum Size (`MinSize`):** Lower capacity floor; ASG will never terminate instances below this count, even during zero-traffic periods.
- **Maximum Size (`MaxSize`):** Upper capacity ceiling; prevents runaway financial costs during anomalous traffic surges or DDoS attacks.
- **Desired Capacity (`DesiredCapacity`):** Default target number of healthy operational instances maintained under normal conditions.

### Scaling Policy Types:
1. **Target Tracking Scaling:** Automatically adjusts capacity to keep a specific metric at a specified target (e.g., maintain average ASG CPU utilization at exactly $60\%$).
2. **Step Scaling:** Increases or decreases capacity in stepped increments based on the magnitude of a metric breach (e.g., add 1 instance if CPU is between $70\%-80\%$; add 3 instances if CPU $> 80\%$).
3. **Scheduled Scaling:** Adjusts instance capacity predictably based on anticipated calendar events (e.g., scale out ahead of an e-commerce flash sale at 09:00 AM).

<br>

## 🔥 Q16. Explain Amazon CloudWatch: Metrics, Alarms, and Automated Actions.

**Answer:**

Amazon CloudWatch provides comprehensive monitoring and operational telemetry across all AWS cloud resources:

### Core Concepts:
1. **Metrics:** Time-ordered data points representing resource performance variables (e.g., `CPUUtilization`, `NetworkIn`, `DiskReadOps`, `5XXError`). CloudWatch gathers standard metrics at 5-minute intervals (or 1-minute intervals with Detailed Monitoring).
2. **Alarms:** Evaluates metric data points over a specified time window against a defined numerical threshold:
   - **OK State:** The metric is within allowable boundaries.
   - **ALARM State:** The metric has crossed the specified threshold for the designated number of evaluation periods.
   - **INSUFFICIENT_DATA State:** Incomplete data points to determine health.
3. **Automated Remediation Actions:**
   - Triggering Auto Scaling policies to add or terminate EC2 instances.
   - Dispatching SNS push notifications to operations teams.
   - Invoking EC2 recovery actions (reboot, stop, or terminate an unresponsive instance).

<br>

## 🔥 Q17. Explain OpenStack architecture and detail five of its core sub-projects.

**Answer:**

OpenStack is a comprehensive open-source cloud operating system that orchestrates compute, storage, and networking hardware:

```
+-------------------------------------------------------+
|                 Horizon (Web Dashboard)               |
+-------------------------------------------------------+
                           |
+-------------------------------------------------------+
|             Keystone (Identity & Auth)                |
+-------------------------------------------------------+
       |                   |                    |
       v                   v                    v
+---------------+  +---------------+  +---------------+
| Nova (Compute)|  |Neutron (Netwk)|  | Glance (Images)|
+---------------+  +---------------+  +---------------+
       |                   |
       v                   v
+---------------+  +---------------+
| Cinder (Block)|  | Swift (Object)|
+---------------+  +---------------+
```

### Five Core Sub-Projects:
1. **Keystone (Identity Service):** Provides centralized authentication, authorization, role token issuance, and service catalog management for all OpenStack components.
2. **Nova (Compute Service):** Controls virtual machine instance lifecycle, communicating with hypervisors (KVM, Xen) to schedule and provision compute resources.
3. **Neutron (Network Service):** Orchestrates virtual networks, routers, IP allocation, security firewalls, and SDN integrations.
4. **Glance (Image Service):** Serves as a centralized repository for virtual machine disk images and server templates.
5. **Cinder (Block Storage Service):** Provides persistent, block-level storage volumes attached directly to running Nova compute instances.

<br>

## 🔥 Q18. What is Service Oriented Architecture (SOA)? Explain its foundational principles.

**Answer:**

**Service Oriented Architecture (SOA)** is an architectural paradigm wherein software components deliver business functionality as independent, loosely coupled, interoperable services accessible over standard networks.

### Foundational SOA Principles:
1. **Standardized Service Contract:** Services define their capabilities, input schemas, and output formats through explicit, standardized interfaces (e.g., WSDL or OpenAPI documents).
2. **Loose Coupling:** Services maintain independence. Internal algorithms, operating systems, and database technologies can be altered without impacting consuming clients.
3. **Service Abstraction:** Services hide internal implementation logic from the outside world, presenting only the public contract.
4. **Service Reusability:** Business logic is designed into modular services reusable across multiple enterprise business workflows.
5. **Service Autonomy:** Each service exercises complete governance and control over its underlying data storage and internal runtime environment.
6. **Service Discoverability:** Services register metadata into centralized registries (e.g., UDDI), allowing clients to discover endpoints dynamically.

<br>

## 🔥 Q19. Detail the mathematical penalty formulation regarding the value of on-demand cloud services.

**Answer:**

When an enterprise owns private data centers, severe financial and operational penalties occur when physical computing capacity fails to match dynamic real-world workload demand:

```
Capacity /
Workload
  ^
  |        /---\          <- Demand D(t)
  |       /     \
  |======/=======\======= <- Fixed Capacity R(t)
  |     /         \
  |    /           \
  +-------------------------> Time (t)
      Under-provisioned     Over-provisioned
      (Lost Business)       (Wasted Money)
```

### Mathematical Penalty Model:
Let $D(t)$ denote instantaneous customer demand at time $t$, and let $R(t)$ denote allocated system resources at time $t$.

1. **Under-Provisioning Penalty ($R(t) < D(t)$):**
   - The infrastructure possesses insufficient resources to fulfill incoming requests, resulting in dropped connections, severe latency spikes, SLA breaches, and lost customer transactions:
     $$\text{Penalty}_{\text{under}} = \int_{R(t) < D(t)} c_u \cdot [D(t) - R(t)] \, dt$$
     *(where $c_u$ is the hourly cost of lost business and brand damage).*
2. **Over-Provisioning Penalty ($R(t) > D(t)$):**
   - The infrastructure maintains surplus servers running idle during off-peak hours, wasting capital on electricity, cooling, and unutilized silicon:
     $$\text{Penalty}_{\text{over}} = \int_{R(t) > D(t)} c_o \cdot [R(t) - D(t)] \, dt$$
     *(where $c_o$ is the idle resource holding cost per unit time).*

**On-Demand Cloud Solution:** Elastic cloud services permit $R(t) \approx D(t)$ dynamically in real time, minimizing the integral penalty loss to near zero.

<br>

## 🔥 Q20. Detail the Three-Tier E-Commerce Cloud Reference Architecture.

**Answer:**

```
                        [ Internet Shoppers ]
                                  |
                                  v
+---------------------------------------------------------------+
|               Tier 1: Load Balancing Tier                     |
| - Redundant AWS Application Load Balancers (ALB)              |
| - SSL/TLS Handshake Termination                               |
| - Distributes incoming traffic across Availability Zones      |
+---------------------------------------------------------------+
                                  |
                                  v
+---------------------------------------------------------------+
|               Tier 2: Application / Compute Tier              |
| - EC2 Auto Scaling Group deployed across Multi-AZ             |
| - Stateless Django / Flask Web Microservices                  |
| - Scaling Policies triggered on CPU utilization / Request TPS |
+---------------------------------------------------------------+
                                  |
                                  v
+---------------------------------------------------------------+
|               Tier 3: Database & Storage Tier                 |
| - Amazon RDS Multi-AZ Relational Database                     |
|   ├── Master Node (Synchronous Writes)                        |
|   └── Read Replicas (Asynchronous Read Queries)               |
| - Redis In-Memory Cache (User Sessions & Shopping Carts)      |
| - Amazon S3 Bucket (Product Catalog Images & Media)           |
+---------------------------------------------------------------+
```

<br>

## 🔥 Q21. Explain how OAuth 2.0 works in cloud application authorization.

**Answer:**

OAuth 2.0 is an industry-standard open authorization framework enabling third-party applications to obtain limited access to user resources hosted on an HTTP service without exposing user credentials:

### Four Core Roles:
1. **Resource Owner:** The end-user granting access to their protected data.
2. **Client Application:** The third-party software seeking access to user data.
3. **Authorization Server:** Authenticates the user and issues cryptographically signed access tokens (e.g., Google Identity, AWS Cognito).
4. **Resource Server:** The backend API holding user resources (e.g., Google Drive API).

### Authorization Code Flow:
```
Client App                   Auth Server                 Resource Server
    |                             |                             |
    |-- 1. Redirect to Login ---->|                             |
    |   (User authenticates &     |                             |
    |    grants consent)          |                             |
    |<-- 2. Auth Code Return -----|                             |
    |                             |                             |
    |-- 3. Exchange Auth Code --->|                             |
    |      + Client Secret        |                             |
    |<-- 4. Issue Access Token ---|                             |
    |                             |                             |
    |-- 5. Request Resource with Access Token (Bearer) -------->|
    |<-- 6. Return Protected User Data -------------------------|
```

<br>

## 🔥 Q22. Explain the difference between Boto3 `client` and `resource` interfaces.

**Answer:**

| Parameter | Boto3 `client` | Boto3 `resource` |
| :--- | :--- | :--- |
| **Abstraction Level** | Low-level service interface; 1-to-1 mapping with raw AWS REST APIs. | High-level, object-oriented abstraction. |
| **Response Format** | Returns raw Python dictionaries formatted directly from underlying JSON responses. | Returns customized Python objects containing member attributes and encapsulated actions. |
| **Service Coverage** | Supports $100\%$ of all AWS services and newest API updates immediately. | Supports only a subset of AWS services (EC2, S3, SQS, DynamoDB); deprecated in newer developments. |
| **Syntax Style** | Explicit function calls requiring explicit parameter passing (e.g., `client.describe_instances()`). | Object-oriented chain methods (e.g., `s3.Bucket('name').objects.all()`). |
| **Recommendation** | Recommended by AWS for all modern enterprise production scripts. | Legacy convenience interface. |

<br>

## 🔥 Q23. Write a Python Boto3 script to launch an EC2 instance with an Apache Web Server UserData script.

**Answer:**

```python
import boto3
import base64

def launch_web_server():
    ec2 = boto3.client('ec2', region_name='ap-south-1')
    
    # Bash script injected via UserData to install and launch Apache upon first boot
    user_data_script = """#!/bin/bash
yum update -y
yum install -y httpd
systemctl start httpd
systemctl enable httpd
echo "<h1>Welcome to Cloud-Native Web Server</h1>" > /var/www/html/index.html
"""
    
    response = ec2.run_instances(
        ImageId='ami-0abcdef1234567890', # Amazon Linux 2023 AMI
        InstanceType='t2.micro',
        MinCount=1,
        MaxCount=1,
        KeyName='production-key',
        SecurityGroupIds=['sg-0123456789abcdef0'],
        UserData=user_data_script, # Automatically base64-encoded by Boto3
        TagSpecifications=[
            {
                'ResourceType': 'instance',
                'Tags': [{'Key': 'Name', 'Value': 'Automated-Apache-Host'}]
            }
        ]
    )
    
    instance_id = response['Instances'][0]['InstanceId']
    print(f"Successfully launched Web Server Instance: {instance_id}")
    return instance_id

if __name__ == '__main__':
    launch_web_server()
```

<br>

## 🔥 Q24. Detail the Model-Template-View (MTV) pattern in Django and its advantages in Cloud Applications.

**Answer:**

Django implements the **MTV (Model-Template-View)** variant of the classic MVC paradigm:

```
Client Request ---> urls.py ---> View (Business Logic) <---> Model (ORM / DB)
                                      |
                                      v
                               Template (HTML/UI) ---> Client Response
```

1. **Model (Data Access Layer):** Represents data structures as Python classes. The built-in ORM translates Python syntax into safe SQL queries, abstracting multi-cloud database migrations between SQLite, MySQL, and PostgreSQL.
2. **Template (Presentation Layer):** A text/HTML file defining the visual user interface, utilizing the Django Template Language (DTL) to bind dynamic data without embedding raw Python code.
3. **View (Controller/Logic Layer):** Contains callback functions that receive HTTP requests, execute business logic, query Models, and pass data dictionaries into Templates for rendering.

### Advantages for Cloud Native Deployments:
- **Stateless Architecture:** Separating business logic from persistent database models enables Django container instances to scale horizontally across multi-AZ clusters.
- **ORM Storage Decoupling:** Integrating `django-storages` allows media assets to be transparently written to object stores (Amazon S3) rather than local container filesystems.

<br>

## 🔥 Q25. Explain the differences between Containerization (Docker) and Traditional Virtualization (VMs).

**Answer:**

| Parameter | Virtual Machines (Hypervisor-Based) | Containers (OS-Level Virtualization) |
| :--- | :--- | :--- |
| **Virtualization Level** | Hardware abstraction; virtualizes underlying physical hardware. | Operating System virtualization; shares host OS kernel. |
| **Guest OS Requirement** | Each VM runs a complete, heavy guest operating system. | No guest OS; containers package application binaries and user-space libraries only. |
| **Boot Time** | Minutes (boots BIOS, kernel initialization, systemd services). | Milliseconds (spawns an isolated host OS process). |
| **Resource Footprint** | Heavy (gigabytes of disk image and gigabytes of pre-allocated RAM). | Extremely lightweight (megabytes of storage and dynamic RAM consumption). |
| **Isolation Boundary** | Hardware-enforced hypervisor boundary; maximum security isolation. | Linux kernel namespaces (PID, NET, IPC) and cgroups; weaker isolation boundary. |
| **Portability** | Hypervisor-dependent disk images (VMDK, VHD, QCOW2). | Complete write-once-run-anywhere container image format (OCI standard). |

```
Virtual Machines:                 Containers:
+-----------------------+         +-----------------------+
| App 1    |   App 2    |         | App 1    |   App 2    |
| Libs     |   Libs     |         | Libs     |   Libs     |
+----------+------------+         +----------+------------+
| Guest OS |  Guest OS  |         | Container Engine      |
+-----------------------+         | (Docker / Containerd) |
|   Hypervisor          |         +-----------------------+
+-----------------------+         | Host Operating System |
| Physical Hardware     |         +-----------------------+
+-----------------------+         | Physical Hardware     |
                                  +-----------------------+
```

<br>

</div>
</div>


<br>


# 🐦‍🔥 TOP 25 HIGH-YIELD POST-MIDSEM EXAMINATION QUESTIONS & MODEL ANSWERS

---

<br>

## 🔥 Q1. Detail the complete MapReduce execution pipeline step-by-step from Input Splits to HDFS storage with an architectural diagram.

**Answer:**

```
[Raw HDFS Data File (e.g., 1 GB)]
               |
               v
[Input Splits (8 splits of 128 MB each)]
               |
               v
[RecordReader] -> Parses raw bytes into (k1, v1) records (e.g., byte_offset, line_text)
               |
               v
[Map Phase]    -> User logic transforms (k1, v1) into intermediate [(k2, v2)]
               |
               v
[Combiner]     -> (Optional mini-reducer) In-memory local aggregation on the Mapper node
               |
               v
[Partitioner]  -> Assigns intermediate keys to Reducers via: hash(k2) % num_reducers
               |
               v
[Shuffle & Sort] -> HTTP network transfer: groups and sorts all values for identical k2
               |
               v
[Reduce Phase] -> User logic aggregates: (k2, list(v2)) -> [(k3, v3)]
               |
               v
[RecordWriter] -> Writes final key-value pairs sequentially into HDFS (3x replicated)
```

### Detailed Pipeline Stages:
1. **Input Splitting & RecordReader:** HDFS files are logically split into chunks (typically 128 MB). A `RecordReader` translates split byte offsets into discrete records `(k1, v1)`.
2. **Map Phase:** An independent Mapper task runs on each split, emitting intermediate `(k2, v2)` pairs to an in-memory buffer (100 MB circular buffer).
3. **Combiner (Mini-Reducer):** If configured, performs local pre-aggregation in memory when the buffer reaches 80% capacity to dramatically shrink network transfer volume.
4. **Partitioner:** Directs keys to target Reducers using hash partitioning ($	ext{hash}(k_2) \pmod{R}$).
5. **Shuffle & Sort:** Copies partitioned data from Mapper nodes to Reducer nodes across the cluster network and sorts records by key.
6. **Reduce Phase:** Invokes the user reduce function once per unique key `k2` over its iterator of values `[v2]`.
7. **RecordWriter:** Formats and writes the final output to persistent HDFS storage.

<br>

## 🔥 Q2. What is a Combiner in MapReduce? Differentiate between a Combiner and a Reducer. When can a Combiner NOT be used?

**Answer:**

A **Combiner** is an optional optimization component in MapReduce that performs **local in-memory pre-aggregation** of intermediate key-value pairs directly on the worker node running the Mapper, before data is sent across the network.

### Differences Between Combiner and Reducer:
| 🌟 Dimension | Combiner | Reducer |
| :--- | :--- | :--- |
| **Execution Location** | Runs locally on the individual **Mapper node**. | Runs on dedicated **Reducer nodes** across the cluster. |
| **Input Data Scope** | Processes only intermediate data produced by a **single Mapper**. | Processes grouped data gathered from **all Mappers** cluster-wide. |
| **Execution Guarantee** | Optional; Hadoop makes no guarantee on execution frequency (0, 1, or multiple times). | Mandatory; guaranteed to execute exactly once per key group. |
| **Primary Purpose** | Bandwidth optimization: shrinks data volume before network Shuffle. | Final aggregation and output production to HDFS. |

### When a Combiner CANNOT be Used:
A Combiner can **only** be safely used if the reduction operation is both **associative and commutative**:
$$f(a,\, f(b, c)) = f(f(a, b),\, c) \quad 	ext{and} \quad f(a, b) = f(b, a)$$
- **Valid (Combiner Allowed):** Summation, Count, Maximum, Minimum.
- **INVALID (Combiner CANNOT be Used):** **Average / Mean**.
  - *Mathematical Justification:* The average of averages does not equal the global average:
    $$rac{10 + 20}{2} = 15; \quad rac{30 + 40 + 50}{3} = 40; \quad 	ext{Combined: } rac{15 + 40}{2} = 27.5$$
    Whereas the true global average is:
    $$rac{10 + 20 + 30 + 40 + 50}{5} = rac{150}{5} = 30 
e 27.5$$
    Using a Combiner for Average produces mathematically incorrect results.

<br>

## 🔥 Q3. Explain the Partitioning Function in MapReduce. How does HashPartitioner prevent reducer workload skew?

**Answer:**

### Role of the Partitioner:
The **Partitioner** sits between the Map phase and the Reduce phase. Its sole responsibility is to assign each intermediate key-value pair `(k2, v2)` produced by Mappers to exactly one target **Reducer task** $r \in [0, R-1]$.

### HashPartitioner Mechanism:
The default partitioner in Apache Hadoop is the **`HashPartitioner`**. It evaluates the Java `hashCode()` of the key modulo the total number of configured reducers:
$$\mathbf{	ext{Target Reducer ID} = \left(	ext{key.hashCode()} \ \& \ 	ext{0x7FFFFFFF}ight) \pmod{	ext{numReducers}}}$$

### Workload Balancing & Mitigating Skew:
- **Uniform Distribution:** A robust hash function projects arbitrary keys uniformly across the range of reducer IDs, preventing a single reducer from being overwhelmed by disproportionate data volumes.
- **Deterministic Key Routing:** It guarantees that **all intermediate values associated with the exact same key are routed to the identical Reducer**, which is required for correct aggregation.
- **Custom Partitioners:** If data possesses severe intrinsic skew (e.g., 90% of web traffic originates from one country), developers implement custom partitioners that isolate skewed keys to dedicated reducers while spreading normal keys evenly.

<br>

## 🔥 Q4. How does HDFS achieve fault tolerance and high availability? Explain Rack Awareness and block replication policy.

**Answer:**

HDFS is engineered to execute reliably on commodity hardware clusters where individual node failures are common.

### 1. Block Replication Policy:
- Files are divided into contiguous blocks (default 128 MB).
- Each block is replicated $N$ times (default replication factor = 3).

### 2. Rack Awareness Placement Algorithm:
To survive switch failures and balance inter-rack network traffic:
- **Replica 1:** Placed on the local DataNode running the client application (or an arbitrary node).
- **Replica 2:** Placed on a DataNode residing in a **different physical rack** (survives rack switch failure).
- **Replica 3:** Placed on a different DataNode in the **same remote rack as Replica 2** (minimizes cross-rack write traffic).
- *Subsequent Replicas (if factor > 3):* Placed on random nodes across different racks.

### 3. Automated Failure Recovery:
- **Heartbeat & Dead Node Detection:** DataNodes send heartbeats every 3 seconds to the NameNode. If no heartbeat arrives for 10 minutes, the node is marked dead.
- **Under-Replication Healing:** The NameNode scans the block namespace, identifies blocks with replica count $< 3$, and immediately schedules background replication to healthy nodes.
- **Active-Standby NameNode HA:** In Hadoop 2.x+, two synchronized NameNodes (Active and Standby) share a distributed transaction log via **Quorum Journal Managers (QJM)** and ZooKeeper, enabling instant sub-second failover.

<br>

## 🔥 Q5. What are the roles of FsImage and EditLog in HDFS NameNode? How does the Secondary NameNode perform checkpointing?

**Answer:**

The NameNode maintains the entire filesystem namespace, directory hierarchy, and file-to-block mappings in high-speed RAM for microsecond lookup performance.

### 1. FsImage and EditLog:
- **`FsImage`:** A point-in-time serialized snapshot of the entire HDFS filesystem namespace and directory structure stored on the NameNode's local disk.
- **`EditLog`:** A write-ahead transaction journal recording every incremental modification (file creation, deletion, rename) made since the last `FsImage` was generated. Every write transaction is flushed to the `EditLog` before being acknowledged to the client.

### 2. The Unbounded Growth Problem:
If the NameNode runs for months, the `EditLog` grows to gigabytes in size. Upon reboot, the NameNode would take hours to replay millions of edits into the `FsImage`, causing extended cluster downtime.

### 3. Checkpointing via Secondary NameNode:
The **Secondary NameNode** (Checkpoint Node) solves this problem by performing scheduled background merges:
```
+-----------------------------------------------------------------------------------+
|                        CHECKPOINTING WORKFLOW SEQUENCE                            |
+-----------------------------------------------------------------------------------+
[NameNode]                                                   [Secondary NameNode]
    |                                                                 |
    | 1. Rolls current EditLog; starts writing new edits to new file   |
    | 2. Sends old EditLog and current FsImage ---------------------> |
    |                                                                 | 3. Loads FsImage into RAM
    |                                                                 | 4. Replays EditLog records
    |                                                                 | 5. Generates compact
    |                                                                 |    new "fsimage.ckpt"
    |                                                                 |
    | <--- 6. Transfers fresh merged "fsimage.ckpt" back -------------+
    |
    | 7. Renames "fsimage.ckpt" to "FsImage"
```

<br>

## 🔥 Q6. Compare Hadoop 1.x (JobTracker/TaskTracker) and Hadoop 2.x/3.x (YARN). What architectural limitations did YARN overcome?

**Answer:**

### Architectural Evolution:
In **Hadoop 1.x**, compute resource management and application processing were tightly coupled within the MapReduce execution engine managed by the **JobTracker** (master) and **TaskTrackers** (slaves).

```
    HADOOP 1.x ARCHITECTURE                        HADOOP 2.x/3.x (YARN) ARCHITECTURE
+-----------------------------+               +----------------------------------------+
|   MapReduce Execution Engine|               | Applications: Spark | Flink | MapReduce|
| (Resource Mgmt + Compute)   |               +----------------------------------------+
+-----------------------------+               | YARN: Decoupled Resource Management    |
|   HDFS Storage              |               +----------------------------------------+
+-----------------------------+               | HDFS / Ozone / Cloud Storage           |
                                              +----------------------------------------+
```

### Limitations of Hadoop 1.x Overcome by YARN:
1. **Single Point of Failure & Scalability Bottleneck:** JobTracker performed both resource scheduling and individual task tracking. It could not scale beyond ~4,000 nodes or 40,000 concurrent tasks. YARN decouples these: ResourceManager handles pure resource allocation, scaling to 10,000+ nodes.
2. **Fixed Map/Reduce Slots:** Hadoop 1.x partitioned hardware into static "Map Slots" and "Reduce Slots". If an application had only Map tasks, Reduce slots sat completely idle, wasting up to 50% of cluster hardware. YARN allocates generic dynamic **Resource Containers** (CPU + RAM), achieving near 100% hardware utilization.
3. **Monolithic Programming Model:** Hadoop 1.x supported only MapReduce batch jobs. YARN transformed Hadoop into a general-purpose distributed cluster OS capable of running Apache Spark, Flink, Storm, and MPI alongside MapReduce.

<br>

## 🔥 Q7. Detail the complete execution lifecycle of an application submitted to a YARN cluster.

**Answer:**

```
[Client]
    |
    | 1. Submits application (JAR, configuration)
    v
[ResourceManager (ApplicationsManager)]
    |
    | 2. Allocates Container 1 on NodeManager A
    v
[NodeManager A] ---> Launches [ApplicationMaster (AM)]
                                      |
    +---------------------------------+---------------------------------+
    | 3. AM evaluates data locality; requests task containers from RM   |
    v                                                                   v
[ResourceManager (Scheduler)]                                           |
    |                                                                   |
    | 4. Grants Container Leases (NodeManager B, NodeManager C) <-------+
    v
[ApplicationMaster]
    |
    | 5. Instructs NodeManagers B and C to launch container processes
    +---------------------------------+---------------------------------+
    |                                 |
    v                                 v
[NodeManager B: Container 2]       [NodeManager C: Container 3]
(Runs Task 1)                      (Runs Task 2)
    |                                 |
    +--- 6. Reports status to AM -----+
                               |
    7. Once complete, AM unregisters with RM; RM releases containers!
```

### Lifecycle Steps:
1. Client submits application to the ResourceManager.
2. The ApplicationsManager negotiates a container from the Scheduler and launches the application's dedicated **ApplicationMaster (AM)**.
3. The AM calculates data locality from HDFS block locations and requests specific resource containers from the ResourceManager Scheduler.
4. The Scheduler grants container allocations.
5. The AM contacts target NodeManagers to launch tasks inside the allocated containers.
6. NodeManagers monitor execution and report container status back to the AM.
7. Upon job completion, the AM unregisters with the RM and releases all containers back to the cluster pool.

<br>

## 🔥 Q8. How does Apache HBase achieve sub-millisecond random writes and reads on top of an append-only distributed file system (HDFS)? Explain MemStore, WAL, and HFiles.

**Answer:**

HBase employs a **Log-Structured Merge-Tree (LSM-Tree)** architecture to provide real-time random read/write access over append-only HDFS storage:

### 1. Sub-Millisecond Random Writes:
1. **Write-Ahead Log (WAL):** When a `Put` request arrives, HBase immediately writes the mutation sequentially to the WAL stored on HDFS. Sequential writes to disk are extremely fast. This guarantees crash durability.
2. **In-Memory MemStore:** Simultaneously, the record is placed into **MemStore**—an in-memory sorted data structure (ConcurrentSkipListMap).
3. Once in MemStore, the write operation is immediately acknowledged to the client with sub-millisecond response time.
4. **HFile Flushing:** When MemStore reaches its threshold (default 128 MB), it flushes sequentially to HDFS as an immutable, indexed **HFile**. Sequential HDFS block creation avoids random disk write overhead.

### 2. Sub-Millisecond Random Point Reads:
To read a record by its `RowKey`:
1. Checks **MemStore** for uncommitted modifications.
2. Checks **BlockCache** (an in-memory LRU cache of frequently accessed HFile blocks).
3. If not cached, it queries **Bloom Filters** associated with each HFile. Bloom filters mathematically determine if a key is definitely NOT present in an HFile, eliminating 99% of unnecessary disk I/O seeks.
4. Performs a single targeted read on the exact HFile block containing the key.

<br>

## 🔥 Q9. What is the role of Apache ZooKeeper in the Hadoop ecosystem? Give two concrete examples (HBase and NameNode HA).

**Answer:**

Apache ZooKeeper is a centralized, highly reliable distributed coordination service providing distributed synchronization, consensus (Zab protocol), group membership, and configuration management across cloud clusters.

### Concrete Example 1: Apache HBase Cluster Coordination:
- **Active HMaster Election:** If multiple HMasters are launched for high availability, ZooKeeper coordinates leader election via ephemeral znodes (`/hbase/master`).
- **RegionServer Health Tracking:** Each RegionServer creates an ephemeral znode upon startup. If a RegionServer crashes or network partitions, its ephemeral znode expires; ZooKeeper alerts the HMaster, which triggers immediate region reassignment to surviving servers.
- **Root Table Location:** Clients query ZooKeeper to discover which RegionServer is hosting the `hbase:meta` system catalog table.

### Concrete Example 2: HDFS NameNode High Availability (Active-Standby Failover):
- The **ZKFailoverController (ZKFC)** runs on both NameNodes.
- Active NameNode holds a lock on an ephemeral znode (`/hadoop-ha/dfs-cluster/ActiveBreadCrumb`).
- If the Active NameNode stops sending heartbeats, the znode drops. ZooKeeper notifies the standby ZKFC, which automatically transitions the Standby NameNode to Active state with zero human intervention.

<br>

## 🔥 Q10. Differentiate between Apache Hive and Apache Pig across five key technical dimensions.

**Answer:**

| 🌟 Dimension | Apache Hive | Apache Pig |
| :--- | :--- | :--- |
| **Language & Style** | **HiveQL (HQL):** Declarative SQL-like query language. | **Pig Latin:** Procedural, high-level dataflow scripting language. |
| **Primary Data Abstraction** | Relational Tables, Rows, Columns, Partitions, Buckets. | Multi-valued nested data models: Atoms, Tuples, Bags, and Maps. |
| **Target User Base** | Business analysts, SQL developers, data reporting teams. | Data engineers, researchers, ETL pipeline architects. |
| **Use Case Focus** | Enterprise Data Warehousing, OLAP aggregations, ad-hoc queries. | Complex ETL pipelines, raw unstructured data cleaning, log parsing. |
| **Extensibility Mechanism** | Hive UDFs (User Defined Functions), UDAFs (Aggregates), UDTFs. | Pig EvalFunc UDFs (implemented in Java, Python/Jython, Ruby). |

<br>

## 🔥 Q11. Explain Schema-on-Read in Apache Hive vs Schema-on-Write in traditional RDBMS. How does Hive Metastore work?

**Answer:**

### Schema-on-Write (Traditional RDBMS):
In traditional relational databases (MySQL, Oracle), the table schema is enforced **when data is inserted or loaded into the database**. The database parses the incoming data, validates constraints, checks column data types, and lays it out in proprietary disk storage. If an incoming record fails validation, the write is aborted. Loading large datasets is time-consuming.

### Schema-on-Read (Apache Hive):
In Apache Hive, raw data files (CSV, TSV, JSON, Parquet) are simply copied directly into HDFS storage **without parsing or verification**. The schema is applied **dynamically when the data is read during query execution**. Hive applies **SerDe (Serializer/Deserializer)** interfaces to interpret raw text lines into structured rows on the fly. This enables instantaneous multi-terabyte data ingestion into the data lake.

### Role of the Hive Metastore:
The **Hive Metastore** is a central repository (typically backed by MySQL or PostgreSQL) that stores all structural metadata:
- Table schemas (column names, data types, comment strings).
- Physical HDFS directory paths mapping to tables.
- Partition key values and file format SerDe definitions.
The Hive compiler contacts the Metastore during query parsing to validate SQL syntax and plan execution stages.

<br>

## 🔥 Q12. Detail the internal execution workflow when an Apache Pig script is compiled and executed in MapReduce mode.

**Answer:**

When a user submits a Pig Latin script in MapReduce mode (`pig -x mapreduce myscript.pig`), the script passes through four compilation phases:

```
[Pig Latin Script]
        |
        v
[1. Parser]             --> Validates syntax, verifies schemas, builds Abstract Syntax Tree (AST)
        |
        v
[2. Logical Plan Gen.]  --> Builds DAG of logical relational operators (LOAD, FILTER, FOREACH, GROUP)
        |
        v
[3. Optimizer]          --> Pushes projections/filters early; eliminates redundant transformations
        |
        v
[4. Physical Plan Gen.] --> Translates logical operations into physical execution primitives
        |
        v
[5. MapReduce Compiler] --> Decomposes physical DAG into a sequence of native Hadoop MapReduce jobs
        |
        v
[6. Execution Engine]   --> Submits JAR jobs to YARN ResourceManager; coordinates HDFS data flow
```

1. **Parser:** Checks syntax, verifies schemas, and outputs an Abstract Syntax Tree.
2. **Logical Plan:** Generates an acyclic directed graph of logical relational operators.
3. **Optimization:** Performs relational algebra optimizations: pushing `FILTER` operations before expensive `JOIN` or `GROUP` operations to prune data early.
4. **Physical Plan & MapReduce Compiler:** Maps logical operators to physical MapReduce constructs (e.g., `GROUP` maps to MapReduce Shuffle/Sort; `FOREACH` maps to Mapper projections). It chains these into executable Java MapReduce JARs.
5. **Execution:** Submits the compiled jobs to YARN and manages pipeline completion.

<br>

## 🔥 Q13. Why is Apache Spark up to 100x faster than Hadoop MapReduce for iterative algorithms and interactive analytics?

**Answer:**

1. **In-Memory Computing Model:**
   - *MapReduce:* Every iteration reads input from disk, writes intermediate map output to local disk, shuffles across the network, and writes final reduce output back to HDFS disk with 3x replication overhead. For an iterative algorithm (e.g., 50 iterations of K-Means), this entails 100 disk read/write cycles.
   - *Spark:* Iterative working datasets are cached in distributed **RAM across Executor JVMs**. Subsequent iterations read directly from memory at memory-bus speeds (gigabytes/sec), avoiding disk I/O and replication overhead.
2. **Advanced DAG Execution Engine:**
   - MapReduce enforces a rigid, two-stage Map-then-Reduce cycle. Multi-stage pipelines require separate jobs.
   - Spark's **DAGScheduler** constructs an arbitrary graph of execution stages, pipelining multiple narrow transformations (e.g., `map` $	o$ `filter` $	o$ `map`) into a single execution stage without materializing intermediate data.
3. **Thread-Based Concurrency:**
   - MapReduce launches a new OS-level process (JVM) for every individual task, incurring severe process creation and JVM startup latency.
   - Spark executes tasks as lightweight **threads** within long-running Executor JVMs, launching tasks in milliseconds.

<br>

## 🔥 Q14. Explain Resilient Distributed Datasets (RDDs). How does Spark achieve fault tolerance using DAG lineage without physical disk replication?

**Answer:**

An **RDD (Resilient Distributed Dataset)** is an immutable, lazily-evaluated, partitioned collection of data records distributed across cluster worker nodes.

### Fault Tolerance via Lineage (DAG Recomputation):
Traditional distributed filesystems (like HDFS) achieve fault tolerance by physically copying every data block 3 times across physical disks, consuming 200% storage overhead and significant network write bandwidth.

Spark avoids physical replication by recording an **RDD Lineage Graph (Directed Acyclic Graph - DAG)**:
- Spark maintains the exact mathematical deterministic sequence of transformations used to construct each RDD partition from external source data (e.g., `HDFS File` $	o$ `map()` $	o$ `filter()` $	o$ `RDD_B`).
- If an executor crashes and an in-memory partition of `RDD_B` is lost:
  1. The Driver detects the missing partition.
  2. Spark consults the lineage DAG.
  3. It schedules a task to recompute **only that specific missing partition** by re-applying the upstream transformations from the source data.
  4. Surviving partitions on other executors remain untouched.

<br>

## 🔥 Q15. Differentiate between Narrow Dependencies and Wide Dependencies in Apache Spark transformations with examples.

**Answer:**

```
      NARROW DEPENDENCY (No Shuffle)                  WIDE DEPENDENCY (Shuffle Required)
   Partition 1 ---> Partition A                  Partition 1 ---+---> Partition A
   Partition 2 ---> Partition B                  Partition 2 ---X---> Partition B
   Partition 3 ---> Partition C                  Partition 3 ---+---> Partition C
   (Local, Pipelineable, Fast)                   (Cross-Network Shuffle, Synchronization)
```

| 🌟 Dimension | Narrow Dependencies | Wide Dependencies |
| :--- | :--- | :--- |
| **Partition Relationship** | Each parent partition is used by **at most one** child partition. | Multiple child partitions depend on data from a **single parent partition**. |
| **Network Shuffle** | **NO network shuffle** required; operations execute locally within executor memory. | **Requires a full network shuffle**; intermediate records are sorted and sent across network. |
| **Pipelining** | Can be pipelined together into a single physical execution stage. | Forms a **stage boundary**; downstream stage cannot start until shuffle completes. |
| **Failure Recovery** | Fast; lost child partition requires recomputing only one parent partition. | Expensive; recomputing a lost partition may require recomputing all parent partitions. |
| **Examples** | `map()`, `filter()`, `flatMap()`, `mapPartitions()` | `groupByKey()`, `reduceByKey()`, `join()`, `distinct()` |

<br>

## 🔥 Q16. Differentiate between Transformations and Actions in Apache Spark. Why are transformations lazily evaluated?

**Answer:**

### Differences:
| 🌟 Dimension | Transformations | Actions |
| :--- | :--- | :--- |
| **Operation Behavior** | Constructs a **new RDD/DataFrame** from an existing one. | Computes a final result and returns a value to Driver or writes to storage. |
| **Evaluation Strategy** | **Lazy Evaluation:** No immediate computation takes place. | **Eager Evaluation:** Triggers immediate execution of the entire DAG. |
| **Return Value** | Returns an `RDD[T]` or `DataFrame`. | Returns a non-RDD value (e.g., `Long`, `Array[T]`, `Unit`). |
| **Examples** | `map()`, `filter()`, `flatMap()`, `groupByKey()`, `sample()` | `collect()`, `count()`, `take()`, `first()`, `saveAsTextFile()` |

### Why Transformations are Lazily Evaluated:
1. **Global Query Optimization (Catalyst Optimizer):** By deferring execution until an Action is requested, Spark can inspect the entire pipeline of transformations. It can combine multiple transformations into a single execution pass (e.g., chaining `filter` followed by `map` into a single loop) and push predicates directly to data sources.
2. **Minimizing Intermediate Data Materialization:** Avoids writing massive intermediate datasets to memory or disk.
3. **Fault Tolerance Efficiency:** Allows Spark to capture the entire lineage DAG cleanly before execution begins.

<br>

## 🔥 Q17. Explain Spark Streaming architecture. How do Discretized Streams (DStreams) work, and how does Spark handle node failures in streaming?

**Answer:**

### Discretized Streams (DStreams) Micro-Batch Model:
Spark Streaming models live real-time continuous data streams as a continuous sequence of small, discrete micro-batches called **DStreams (Discretized Streams)**.
- Incoming data is buffered over a small user-configured time window $\Delta t$ (e.g., 500ms to 2 seconds).
- Each micro-batch interval produces a standard Spark RDD containing all events ingested during that interval.
- The standard Spark Core engine processes these RDDs using standard parallel transformations.

### Fault Tolerance Architecture:
1. **Worker Node Failure:**
   - Any RDD partition generated during streaming is immutable and possesses a deterministic lineage DAG. Lost partitions are automatically recomputed from upstream data.
2. **Write-Ahead Logs (WAL):**
   - For streaming sources with potential message loss, streaming receivers synchronously write received bytes to a Write-Ahead Log in durable distributed storage (HDFS/S3). If an executor crashes, the replacement executor recovers uncommitted records from the WAL.
3. **Driver Failure & State Checkpointing:**
   - For stateful operations (e.g., `window`, `updateStateByKey`), Spark periodically checkpoints state RDDs and DAG metadata to HDFS. If the Driver process crashes, a new Driver resumes from the last checkpointed state with zero data loss.

<br>

## 🔥 Q18. Detail the steps to implement a machine learning classification pipeline in Apache Spark MLlib (e.g., predicting on the Adult Census dataset).

**Answer:**

Apache Spark MLlib utilizes the **Pipeline API** (inspired by scikit-learn) to construct reproducible machine learning workflows:

```python
from pyspark.sql import SparkSession
from pyspark.ml import Pipeline
from pyspark.ml.feature import StringIndexer, OneHotEncoder, VectorAssembler
from pyspark.ml.classification import LogisticRegression
from pyspark.ml.evaluation import BinaryClassificationEvaluator

# 1. Initialize SparkSession
spark = SparkSession.builder.appName("AdultCensusPipeline").getOrCreate()

# 2. Load Dataset from HDFS
df = spark.read.csv("hdfs://cluster/data/adult.csv", header=True, inferSchema=True)

# 3. Stage 1: Categorical Feature String Indexing
workclass_indexer = StringIndexer(inputCol="workclass", outputCol="workclass_idx")
education_indexer = StringIndexer(inputCol="education", outputCol="education_idx")
label_indexer = StringIndexer(inputCol="income", outputCol="label")

# 4. Stage 2: Feature Vector Assembly
feature_cols = ["age", "hours_per_week", "workclass_idx", "education_idx"]
assembler = VectorAssembler(inputCols=feature_cols, outputCol="features")

# 5. Stage 3: Estimator (Classifier)
lr = LogisticRegression(featuresCol="features", labelCol="label", maxIter=20)

# 6. Chain Stages into an End-to-End Pipeline
pipeline = Pipeline(stages=[workclass_indexer, education_indexer, label_indexer, assembler, lr])

# 7. Train-Test Split and Model Fitting
train_df, test_df = df.randomSplit([0.8, 0.2], seed=42)
pipeline_model = pipeline.fit(train_df)

# 8. Model Evaluation
predictions = pipeline_model.transform(test_df)
evaluator = BinaryClassificationEvaluator(labelCol="label", metricName="areaUnderROC")
auc = evaluator.evaluate(predictions)
print(f"Area Under ROC (AUC): {auc:.4f}")
```

<br>

## 🔥 Q19. How is the K-Means clustering algorithm parallelized using the MapReduce framework? Detail the Map, Combine, and Reduce phases.

**Answer:**

### Objective:
Given $n$ $d$-dimensional data points $\mathbf{x}_i$ and $k$ cluster centroids $\{\mathbf{c}_1, \dots, \mathbf{c}_k\}$, K-Means iteratively minimizes within-cluster variance.

### MapReduce Parallelization Strategy:
The massive dataset of data points resides on HDFS. Centroids are small ($k 	imes d$ floats) and are broadcast to all cluster nodes via the DistributedCache.

```
[Broadcast Centroids {C_1, ..., C_k}]
                  |
                  v
[Mapper Phase]    -> Reads sample x; computes Euclidean distance to all centroids;
                     Finds nearest centroid index j = argmin ||x - C_j||;
                     Emits: (j, x)
                  |
                  v
[Combiner Phase]  -> Performs local vector summation on mapper node:
                     Emits: (j, (partial_sum_vector, local_count))
                  |
                  v
[Shuffle & Sort]  -> Gathers all partial sums and counts for centroid j
                  |
                  v
[Reducer Phase]   -> Aggregates global vector sum and global point count:
                     Computes new centroid coordinates: C_j_new = global_sum / global_count;
                     Emits: (j, C_j_new)
                  |
                  v
[Driver Loop]     -> Checks if ||C_j_new - C_j_old|| < epsilon. If not converged, repeats!
```

- **Mapper:** Computes distance between point $\mathbf{x}$ and all $k$ centroids. Emits `(centroid_id, point)`.
- **Combiner:** Locally pre-aggregates points to emit `(centroid_id, (local_vector_sum, local_count))`, drastically shrinking network shuffle traffic.
- **Reducer:** Sums all partial vector sums and counts across all mappers for centroid $j$. Divides total vector sum by total count to yield the updated centroid $\mathbf{c}_j^{new}$.
- **Driver:** Compares old and new centroids. If maximum shift $< \epsilon$ or maximum iterations reached, terminates; otherwise updates centroids file and triggers the next MapReduce iteration.

<br>

## 🔥 Q20. Detail the K-Nearest Neighbors (KNN) classification algorithm using MapReduce. Explain how pairwise distance computations and top-K sorting are distributed.

**Answer:**

### Problem Definition:
Given an unlabelled query test sample $\mathbf{q}$ and a distributed training dataset of millions of labeled points $\{(\mathbf{x}_i, y_i)\}$, find the $K$ points in the training set closest to $\mathbf{q}$ and predict the class via majority voting.

### Distributed Execution Design:
1. **Query Point Broadcast:** The test sample $\mathbf{q}$ is distributed to all Mappers via configuration or distributed cache.
2. **Mapper Phase (Parallel Pairwise Distance Calculation):**
   - Each Mapper processes its local split of training samples.
   - For every sample $(\mathbf{x}_i, y_i)$, it calculates Euclidean distance $d_i = \|\mathbf{x}_i - \mathbf{q}\| = \sqrt{\sum_{j=1}^m (x_{ij} - q_j)^2}$.
   - To optimize network transfer, each Mapper can maintain a local bounded **Max-Heap of size $K$** and emit only its local top-$K$ smallest distances.
   - Emits: `(dummy_key=1, (distance, label))`.
3. **Shuffle & Sort:** All candidate pairs converge to a single Reducer (or a small set of Reducers).
4. **Reducer Phase (Global Top-K Selection & Majority Voting):**
   - The Reducer maintains a global Max-Heap of size $K$.
   - Iterates through all incoming pairs, keeping only the $K$ smallest distances globally.
   - Extracts the class labels of the final $K$ nearest neighbors and executes majority voting:
     $$\hat{y} = rg\max_{c} \sum_{i=1}^K I(y_i = c)$$
   - Outputs the predicted class $\hat{y}$ for test sample $\mathbf{q}$.

<br>

## 🔥 Q21. Explain SAML-based Single Sign-On (SSO). Diagram the complete authentication sequence between User, Service Provider, and Identity Provider.

**Answer:**

### SAML 2.0 Web Browser SSO Sequence:

```
[User Browser (Principal)]       [Service Provider (SP)]       [Identity Provider (IdP)]
           |                                |                              |
           | 1. GET /protected-resource     |                              |
           |------------------------------->|                              |
           |                                |                              |
           | 2. 302 Redirect to IdP         |                              |
           |    with encoded <AuthnRequest> |                              |
           |<-------------------------------|                              |
           |                                                               |
           | 3. GET /sso-login with <AuthnRequest>                         |
           |-------------------------------------------------------------->|
           |                                                               |
           | 4. Prompts user for credentials & MFA challenge               |
           |<------------------------------------------------------------->|
           |    (IdP verifies credentials against internal User Directory) |
           |                                                               |
           | 5. Generates cryptographically signed XML <SAMLResponse>      |
           |    Returns HTML form with embedded assertion                  |
           |<--------------------------------------------------------------|
           |                                                               |
           | 6. HTTP POST /acs with signed SAML Assertion                  |
           |------------------------------->|                              |
           |                                | 7. Verifies IdP signature    |
           |                                |    via pre-shared X.509 cert;|
           |                                |    Extracts user identity;   |
           |                                |    Creates local session.    |
           | 8. 200 OK: Protected Dashboard |                              |
           |<-------------------------------|                              |
```

### Key Elements:
- **SP-Initiated Flow:** User begins by accessing the cloud application (SP).
- **Zero Credential Sharing:** The SP never touches or stores the user's password.
- **IdP Authority:** The Identity Provider performs authentication and signs the XML assertion using its private key.

<br>

## 🔥 Q22. Explain the OAuth 2.0 authorization framework. Detail the roles, token lifecycle, and the Authorization Code Grant flow.

**Answer:**

OAuth 2.0 is an authorization protocol enabling third-party applications to obtain limited access to an HTTP service on behalf of a resource owner without sharing the user's credentials.

### Four Core Roles:
1. **Resource Owner:** The end-user owning the data.
2. **Client:** The third-party application requesting access.
3. **Resource Server:** The API server hosting protected resources.
4. **Authorization Server:** The server authenticating the user and issuing access tokens.

### Authorization Code Flow:
```
[User / Browser]            [Client Web App]            [Authorization Server]        [Resource Server API]
       |                            |                              |                            |
       | 1. Clicks "Login with Google"                             |                            |
       |<---------------------------|                              |                            |
       | 2. Redirects to Auth Server with client_id, scope, redirect_uri                        |
       |---------------------------------------------------------->|                            |
       | 3. Prompts user for credentials & consent                 |                            |
       |<--------------------------------------------------------->|                            |
       | 4. Redirects to Client redirect_uri with ?code=AUTH_CODE  |                            |
       |--------------------------->|                              |                            |
       |                            | 5. POST /token (AUTH_CODE, client_secret)                 |
       |                            |----------------------------->|                            |
       |                            | 6. Validates code; Returns Access Token & Refresh Token   |
       |                            |<-----------------------------|                            |
       |                            |                                                           |
       |                            | 7. API Call: GET /userinfo (Bearer ACCESS_TOKEN)          |
       |                            |---------------------------------------------------------->|
       |                            | 8. Verifies token; Returns protected user data            |
       |                            |<----------------------------------------------------------|
```

<br>

## 🔥 Q23. Explain how Time-based One-Time Password (TOTP) algorithm works mathematically (RFC 6238) and why it resists replay attacks.

**Answer:**

### Mathematical Formulation:
TOTP generates short-lived numeric passcodes based on a pre-shared secret key $K$ and the current time:

1. **Calculate Moving Factor (Time Counter $T$):**
   $$\mathbf{T = \left\lfloor rac{	ext{Current\_Unix\_Time} - T_0}{T_X} ightfloor}$$
   where $T_0 = 0$ (Unix Epoch: Jan 1, 1970 UTC) and $T_X$ is the time step (default = **30 seconds**).
2. **Generate HMAC Hash:**
   $$\mathbf{H = 	ext{HMAC-SHA-1}(K,\, T)}$$
   $H$ is a 20-byte (160-bit) hash digest.
3. **Dynamic Truncation (Extract 4-byte integer):**
   - Take the last 4 bits of $H[19]$ as offset: $	ext{offset} = H[19] \ \& \ 	ext{0x0F}$.
   - Extract a 31-bit positive integer starting from byte offset:
     $$	ext{code} = \left((H[	ext{offset}] \ \& \ 	ext{0x7F}) \ll 24ight) \ | \ \left(H[	ext{offset}+1] \ll 16ight) \ | \ \left(H[	ext{offset}+2] \ll 8ight) \ | \ H[	ext{offset}+3]$$
4. **Modulo Reduction (6 Digits):**
   $$\mathbf{	ext{TOTP} = 	ext{code} \pmod{10^6}}$$

### Why it Resists Replay Attacks:
- Every generated passcode is valid **only for that single 30-second time interval $T$**.
- Once a user enters a passcode and it is verified, the server caches the counter value $T$ for that user. If an eavesdropper captures the passcode over the network and attempts to replay it, the server rejects it because either:
  1. The 30-second window has expired ($T_{	ext{current}} > T_{	ext{token}}$).
  2. The server marks the token for interval $T$ as already used, enforcing single-use semantics.

<br>

## 🔥 Q24. Explain Diffie-Hellman Key Exchange mathematically. Why is it vulnerable to Man-in-the-Middle (MitM) attacks, and how do digital certificates resolve this?

**Answer:**

### Mathematical Protocol:
Alice and Bob agree publicly on a large prime $p$ and a generator base $g$ ($g < p$).

```
        ALICE                                                  BOB
1. Selects private secret integer a.                 1. Selects private secret integer b.
2. Computes Public Value:                            2. Computes Public Value:
   A = (g^a) mod p                                      B = (g^b) mod p
3. Sends A to Bob ===============[Public Network]===============> Sends B to Alice
4. Computes Shared Secret:                           3. Computes Shared Secret:
   S_Alice = (B^a) mod p                                S_Bob = (A^b) mod p
   S_Alice = ((g^b)^a) mod p = (g^(ab)) mod p           S_Bob = ((g^a)^b) mod p = (g^(ab)) mod p

===> Both Alice and Bob now possess identical secret: S = (g^(ab)) mod p!
```

An eavesdropper seeing $g, p, A, B$ cannot compute $S$ due to the intractability of the **Discrete Logarithm Problem**.

### Man-in-the-Middle (MitM) Vulnerability:
Diffie-Hellman provides **no authentication of communicating parties**. An active attacker (Eve) on the network wire can intercept Alice's public value $A$ and substitute her own value $E_A$, and intercept Bob's value $B$ and substitute $E_B$. Alice establishes a shared secret with Eve, and Bob establishes a shared secret with Eve. Eve decrypts, inspects, and re-encrypts all traffic.

### Resolution via Digital Certificates (PKI & TLS):
In modern protocols (e.g., **ECDHE in TLS 1.3**), Diffie-Hellman is combined with **asymmetric digital signatures**. The server sends its public DH parameters signed by its private key, accompanied by an X.509 digital certificate signed by a trusted Certificate Authority (CA). The client verifies the CA signature, authenticating that the public DH key belongs to the legitimate server, preventing MitM spoofing.

<br>

## 🔥 Q25. Detail the systematic seven-step cloud application benchmarking methodology. What are the key metrics measured, and how are bottlenecks identified and tuned?

**Answer:**

Benchmarking evaluates application scalability and identifies performance bottlenecks under synthetic loads.

```
+-----------------------------------------------------------------------------------+
|                        7-STEP BENCHMARKING METHODOLOGY                            |
+-----------------------------------------------------------------------------------+
[Step 1: Define Objectives & SLAs]  --> Specify target RPS, max P99 latency, and cost limits
                 |
                 v
[Step 2: Setup Test Environment]    --> Deploy isolated staging mirror of production
                 |
                 v
[Step 3: Workload Generation]       --> Inject load using JMeter, Locust, wrk, or Gatling
                 |
                 v
[Step 4: Metric & Telemetry Mon.]   --> Track CPU, RAM, IOPS, and network across all tiers
                 |
                 v
[Step 5: Bottleneck Analysis]       --> Profile slow queries, thread locks, and pool limits
                 |
                 v
[Step 6: Tuning & Optimization]     --> Add DB indexes, enable Redis caching, scale workers
                 |
                 v
[Step 7: Verification & Validation] --> Re-run benchmark to verify SLA compliance!
```

### Key Metrics Measured:
- **Throughput:** Requests Per Second (RPS) or Transactions Per Second (TPS).
- **Latency Percentiles:** Median (P50), P95, and P99 tail latency.
- **Resource Utilization:** CPU utilization %, memory saturation, disk read/write IOPS, and network bandwidth.
- **Error Rate:** Percentage of HTTP 5xx errors or dropped connections.

### Bottleneck Identification & Tuning Actions:
1. **Database Tier Bottleneck:** High CPU on database and slow query logs.
   - *Tuning:* Add B-tree indexes, optimize query execution plans, deploy **Amazon ElastiCache Redis** for read-heavy caching, configure Aurora read replicas.
2. **Application Worker Saturation:** High latency with low database load indicates application server thread pool exhaustion.
   - *Tuning:* Increase Gunicorn worker count (`2 * vCPU + 1`), enable asynchronous I/O (AsyncIO/Gevent), and tune thread pool sizes.
3. **Connection Pool Exhaustion:** HTTP 500 errors during sudden traffic spikes.
   - *Tuning:* Deploy connection pooling proxies (e.g., PgBouncer, AWS RDS Proxy) to reuse database connections.

<br>
