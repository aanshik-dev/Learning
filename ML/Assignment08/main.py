import subprocess
import sys

print("==================================================")
print("RUNNING CS360 LAB PRACTICE ASSIGNMENT 7")
print("==================================================")

print("\n>>> STEP 1: Running Question 1 (DBSCAN Clustering)...")
res1 = subprocess.run([sys.executable, 'Assignment08/q1_dbscan.py'])
if res1.returncode != 0:
    print("Question 1 encountered an error.")
    sys.exit(res1.returncode)

print("\n>>> STEP 2: Running Question 2 (Hierarchical Clustering)...")
res2 = subprocess.run([sys.executable, 'Assignment08/q2_hierarchical.py'])
if res2.returncode != 0:
    print("Question 2 encountered an error.")
    sys.exit(res2.returncode)

print("\n==================================================")
print("ALL ASSIGNMENT TASKS COMPLETED SUCCESSFULLY")
print("Generated plots saved in: Assignment08/plots/")
print("Generated results saved in: Assignment08/output/")
print("==================================================")
