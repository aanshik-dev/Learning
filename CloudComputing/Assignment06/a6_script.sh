#!/bin/bash
exec > /var/log/user-data.log 2>&1

# Update packages and install python dependencies
apt-get update -y
apt-get install -y python3 python3-pip python3-flask
pip3 install --break-system-packages pymysql mysql-connector-python || pip install pymysql mysql-connector-python

# Create application directory
mkdir -p /home/ubuntu/app

# Write Flask application code
cat << 'EOF' > /home/ubuntu/app/app.py
# Name: Ansik Singh Tomar
# Roll No: 2401037

from flask import Flask, render_template_string, request, redirect, url_for
import pymysql

app = Flask(__name__)

# Database Configuration
DB_HOST = "__DB_HOST__"
DB_USER = "__DB_USER__"
DB_PASS = "__DB_PASS__"
DB_NAME = "__DB_NAME__"

def get_db():
    return pymysql.connect(
        host=DB_HOST,
        user=DB_USER,
        password=DB_PASS,
        database=DB_NAME,
        cursorclass=pymysql.cursors.DictCursor,
        autocommit=True
    )

def init_db():
    try:
        conn = get_db()
        with conn.cursor() as cursor:
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS feedbacks (
                    id INT AUTO_INCREMENT PRIMARY KEY,
                    name VARCHAR(100) NOT NULL,
                    email VARCHAR(100) NOT NULL,
                    message TEXT NOT NULL,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                );
            """)
        conn.close()
        print("Database initialized successfully.")
    except Exception as e:
        print("Database initialization error:", e)

# HTML template with modern styling
HTML_TEMPLATE = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Ansik Singh Tomar | Personal Portfolio & Feedback</title>
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap" rel="stylesheet">
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Inter', sans-serif; }
        body { background: #0b0f19; color: #f1f5f9; min-height: 100vh; padding: 40px 20px; }
        .container { max-width: 800px; margin: 0 auto; }
        
        .profile-card {
            background: linear-gradient(135deg, #1e293b, #0f172a);
            border: 1px solid #334155;
            padding: 30px;
            border-radius: 16px;
            margin-bottom: 30px;
            box-shadow: 0 10px 25px rgba(0,0,0,0.4);
        }
        .badge {
            display: inline-block;
            background: rgba(99, 102, 241, 0.15);
            color: #818cf8;
            padding: 4px 12px;
            border-radius: 20px;
            font-size: 0.85rem;
            font-weight: 600;
            margin-bottom: 12px;
            border: 1px solid rgba(99, 102, 241, 0.3);
        }
        h1 { font-size: 2rem; color: #fff; margin-bottom: 6px; }
        .subtitle { color: #94a3b8; font-size: 0.95rem; margin-bottom: 16px; }
        .info-grid { display: flex; gap: 20px; flex-wrap: wrap; margin-top: 15px; border-top: 1px solid #334155; padding-top: 15px; }
        .info-item { font-size: 0.88rem; color: #cbd5e1; }
        .info-item strong { color: #38bdf8; }

        .card {
            background: #1e293b;
            border: 1px solid #334155;
            padding: 30px;
            border-radius: 16px;
            margin-bottom: 30px;
            box-shadow: 0 10px 25px rgba(0,0,0,0.3);
        }
        h2 { font-size: 1.35rem; color: #f8fafc; margin-bottom: 20px; display: flex; align-items: center; gap: 8px; }
        .form-group { margin-bottom: 16px; }
        label { display: block; font-size: 0.88rem; color: #94a3b8; margin-bottom: 6px; }
        input, textarea {
            width: 100%;
            padding: 12px 14px;
            background: #0f172a;
            border: 1px solid #334155;
            border-radius: 8px;
            color: #fff;
            font-size: 0.95rem;
            outline: none;
            transition: border-color 0.2s;
        }
        input:focus, textarea:focus { border-color: #6366f1; }
        button {
            background: linear-gradient(135deg, #6366f1, #4f46e5);
            color: white;
            border: none;
            padding: 12px 24px;
            font-size: 1rem;
            font-weight: 600;
            border-radius: 8px;
            cursor: pointer;
            width: 100%;
            transition: opacity 0.2s, transform 0.1s;
        }
        button:hover { opacity: 0.95; transform: translateY(-1px); }

        .feedback-item {
            background: #0f172a;
            border: 1px solid #334155;
            border-radius: 10px;
            padding: 18px;
            margin-bottom: 14px;
        }
        .fb-header { display: flex; justify-content: space-between; align-items: baseline; margin-bottom: 8px; }
        .fb-name { font-weight: 600; color: #38bdf8; font-size: 1rem; }
        .fb-email { color: #64748b; font-size: 0.82rem; margin-left: 6px; }
        .fb-time { color: #64748b; font-size: 0.78rem; }
        .fb-msg { color: #cbd5e1; font-size: 0.92rem; line-height: 1.5; }
        .empty-state { text-align: center; color: #64748b; padding: 20px 0; font-size: 0.95rem; }
    </style>
</head>
<body>
    <div class="container">
        <div class="profile-card">
            <div class="badge">CS351 - Cloud Computing (Assignment 6)</div>
            <h1>Ansik Singh Tomar</h1>
            <div class="subtitle">Roll No: 2401037 | Personal Portfolio & Live Feedback System</div>
            <div class="info-grid">
                <div class="info-item">Architecture: <strong>EC2 + RDS MySQL</strong></div>
                <div class="info-item">Database: <strong>feedback_db</strong></div>
                <div class="info-item">Region: <strong>ap-south-1</strong></div>
            </div>
        </div>

        <div class="card">
            <h2>Leave a Feedback</h2>
            <form method="POST" action="/submit">
                <div class="form-group">
                    <label for="name">Your Name</label>
                    <input type="text" id="name" name="name" placeholder="Enter your full name" required>
                </div>
                <div class="form-group">
                    <label for="email">Email Address</label>
                    <input type="email" id="email" name="email" placeholder="name@example.com" required>
                </div>
                <div class="form-group">
                    <label for="message">Message / Comment</label>
                    <textarea id="message" name="message" rows="4" placeholder="Write your feedback here..." required></textarea>
                </div>
                <button type="submit">Submit Feedback</button>
            </form>
        </div>

        <div class="card">
            <h2>Visitor Feedback (Stored in RDS MySQL)</h2>
            {% if feedbacks %}
                {% for fb in feedbacks %}
                    <div class="feedback-item">
                        <div class="fb-header">
                            <div>
                                <span class="fb-name">{{ fb['name'] }}</span>
                                <span class="fb-email">&lt;{{ fb['email'] }}&gt;</span>
                            </div>
                            <span class="fb-time">{{ fb['created_at'] }}</span>
                        </div>
                        <div class="fb-msg">{{ fb['message'] }}</div>
                    </div>
                {% endfor %}
            {% else %}
                <div class="empty-state">No feedback submitted yet. Be the first to submit above!</div>
            {% endif %}
        </div>
    </div>
</body>
</html>
"""

@app.route('/')
def index():
    feedbacks = []
    try:
        conn = get_db()
        with conn.cursor() as cursor:
            cursor.execute("SELECT id, name, email, message, created_at FROM feedbacks ORDER BY id DESC")
            feedbacks = cursor.fetchall()
        conn.close()
    except Exception as e:
        print("Error fetching feedbacks:", e)
    return render_template_string(HTML_TEMPLATE, feedbacks=feedbacks)

@app.route('/api/feedbacks')
def api_feedbacks():
    feedbacks = []
    try:
        conn = get_db()
        with conn.cursor() as cursor:
            cursor.execute("SELECT id, name, email, message, created_at FROM feedbacks ORDER BY id DESC")
            feedbacks = cursor.fetchall()
        conn.close()
        for fb in feedbacks:
            if 'created_at' in fb and fb['created_at']:
                fb['created_at'] = str(fb['created_at'])
    except Exception as e:
        print("Error in /api/feedbacks:", e)
    return {"feedbacks": feedbacks}

@app.route('/submit', methods=['POST'])
def submit():
    name = request.form.get('name', '').strip()
    email = request.form.get('email', '').strip()
    message = request.form.get('message', '').strip()

    if name and email and message:
        try:
            conn = get_db()
            with conn.cursor() as cursor:
                cursor.execute(
                    "INSERT INTO feedbacks (name, email, message) VALUES (%s, %s, %s)",
                    (name, email, message)
                )
            conn.close()
        except Exception as e:
            print("Error inserting feedback:", e)

    return redirect(url_for('index'))

if __name__ == '__main__':
    init_db()
    app.run(host='0.0.0.0', port=80)
EOF

# Create systemd service for the Flask application
cat << 'EOF' > /etc/systemd/system/feedback-app.service
[Unit]
Description=Flask Portfolio and Feedback Application
After=network.target

[Service]
User=root
WorkingDirectory=/home/ubuntu/app
ExecStart=/usr/bin/python3 /home/ubuntu/app/app.py
Restart=always
RestartSec=5

[Install]
WantedBy=multi-user.target
EOF

# Enable and start the service
systemctl daemon-reload
systemctl enable feedback-app
systemctl start feedback-app
