# Name: Satish Tailor
# Roll No: 2401176

from flask import Flask, render_template

application = Flask(__name__)


# Home page route
# Input: HTTP GET request
# Output: Personal website HTML page
@application.route("/")
def home():
    return render_template("index.html")


# Start Flask application
if __name__ == "__main__":
    application.run(host="0.0.0.0", port=5000)