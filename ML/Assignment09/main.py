import os
import sys
import subprocess

script_dir = os.path.dirname(os.path.abspath(__file__))

print("==================================================")
print("RUNNING CS360 LAB PRACTICE ASSIGNMENT 8 (ASSIGNMENT 09)")
print("==================================================")

tasks = [
    ("Question 1 (K-NN & Weighted K-NN on Heart Disease)", os.path.join(script_dir, "q1_knn.py")),
    ("Question 2 (Sigmoid OVA on Iris Dataset)", os.path.join(script_dir, "q2_sigmoid_ova.py")),
    ("Question 3 (Single-Layer Perceptron on Iris Dataset)", os.path.join(script_dir, "q3_slp.py")),
    ("Question 4 (MLP Back-propagation on XOR Gate)", os.path.join(script_dir, "q4_mlp_xor.py")),
    ("Question 5 (MLP Back-propagation on Pima Diabetes)", os.path.join(script_dir, "q5_mlp_diabetes.py")),
]

for idx, (task_desc, script_path) in enumerate(tasks, 1):
    print(f"\n>>> STEP {idx}: Running {task_desc}...")
    res = subprocess.run([sys.executable, script_path])
    if res.returncode != 0:
        print(f"\n[ERROR] Step {idx} encountered an error (exit code {res.returncode}). Aborting.")
        sys.exit(res.returncode)

print("\n==================================================")
print("ALL ASSIGNMENT 09 TASKS COMPLETED SUCCESSFULLY!")
print(f"Generated plots saved in:  {os.path.join(script_dir, 'plots')}")
print(f"Generated results saved in: {os.path.join(script_dir, 'output')}")
print("==================================================")

