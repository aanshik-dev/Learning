<!-- GitHub Cheatsheet -->
<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **GITHUB CHEATSHEET** 🔥🐦‍🔥

<br>

## 🐦‍🔥 TERMS

- Local - Laptop
- remote - Github

<br>

## 🐦‍🔥 WORKFLOW

> Configure Git ➖🔶 Github repo ➖🔶 Clone ➖🔶 changes ➖🔶 git init ➖🔶 git remote add ➖🔶 add ➖🔶 commit ➖🔶 push

<br>

## 🐦‍🔥 GIT CONFIGURE

- `git config --global user.name  "gitHubUsername"`
- `git config --global user.email  "gitHubEmail"`

<br>

## 🐦‍🔥 COMMANDS

## 🔥 Basic Commands

| General Commands     | Usage                  |
| :------------------- | :--------------------- |
| cd ./perent/child    | Change Directory       |
| cd ..                | Return to parent       |
| mkdir directory_name | Create new folder      |
| clear                | Clears the terminal    |
| ls                   | list all elements      |
| ls -a                | shows all hidden files |

<br>

## 🔥 Git Commands

### 🔶 Remote to Local

- `git clone https://github.com/aanshik-dev/repo.git ` //Brings all file to local
- `git pull origin main ` // brings all changes from remote to local

### 🔶 Local to Remote

- `git init ` // to initiate git in your folder
- `git remote add origin(name) git-link ` // adds remote
- `git remote remove origin ` // removes link remote/repository
- `git remote -v ` // Used to verify remote
- `git branch` // to check branch
- `git branch -M main(new name)` // to rename the current branch
- `git branch checkout -b new-branch-name ` // create and switch to new branch
- `git branch checkout branch-name` // to change branch
- `git branch -d branch-name ` // deletes a branch when on another branch
- `git diff branch-name ` // gives differences between two branches
- `git merge filename ` // merge current branch with other branch
- `git push name (branch) ` // push project to github. Ex-`git push origin main`
- `git push -u origin main ` // shortcut to push to same location

### 🔶 Modified & Untracked Files

- `git add filename ` // adds file to stage
- `git add . ` // adds all files to stage
- `git commit -m "comment the change" ` // commit changes with a message
- `git status ` // shows the sync status of local

### 🔶 ERROR CORRECTION

- `git log` // lShows the commit history (commit hash, author, date, message)
- `git reset` // Unstages all staged files (moves from staging area back to working directory)
- `git reset filename` // Unstages a specific file (keeps file changes)
- `git reset HEAD~1` // Moves HEAD to one commit earlier, Keeps file changes (they become unstaged)
- `git reset --soft HEAD~1` // Moves HEAD to one commit earlier, Keeps file changes staged
- `git push --force` // Forcefully updates the remote branch, Overwrites remote commit history
- `git reset commit-hash-code` // resets to perticular commit, Keeps file changes (unstaged)
- `git reset --hard commit-hash-code` // Resets to a specific commit, Deletes all changes after that commit (staged + unstaged), Working directory also changes (VS Code updates)

### 🔶 FORK

- Makes copy of github repo in your account to make changes and contribute

<br>

## 🐦‍🔥 GIT COLLAB

- Team Head Creates a project
- Team Member forks the project, adds contribution and then requests pull request

To avoid conflicts, the team does not push to the main branch, but creates a feature branch and then merge it to main.

### 🔥 1. The Branching Strategy (Crucial)

Never push code directly to the main branch. This keeps the "production" code stable. Instead, use a Feature Branch workflow:

- Main Branch: The stable, working version of the project.
- Feature Branches: Each member creates a new branch for a specific task (e.g., frontend-login-ui, backend-api-auth, db-schema-setup).

### 🔥 2. The Collaborative Workflow

Each time someone starts working, they should follow these steps:

⚡`Pull the latest changes:` Ensure your local machine has the most recent code from the team.

```bash
git checkout main
git pull origin main
```

⚡ `Create a new branch:`

```bash
git checkout -b feature/your-task-name
```

⚡ `Code and Commit:` Work inside your specific folder (frontend, backend, etc.).

```bash
git add .
git commit -m "Add: functional login form"
```

⚡ `Push to GitHub:`

```bash
git push origin feature/your-task-name
```

### 🔥 3. Pull Requests (PRs) & Code Review

Once you push your branch, go to GitHub and open a Pull Request.

- This asks the team to "merge" your code into the main branch.

- The other team members should look at your code, leave comments, and eventually "Approve" it.

- The DB person should especially review backend PRs that affect how data is fetched.

</div>
</div>
