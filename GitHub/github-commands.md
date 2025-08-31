<div style= "width: 100%; background-image: url(assets/paper.jpg); background-size: contain;">

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

🔸 `git config --global user.name  "gitHubUsername"`
🔸 `git config --global user.email  "gitHubEmail"`

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

🔸 `git clone https://github.com/aanshik-dev/Example.git `
🔸 `git clone https://github.com/aanshik-dev/Example.git ` //Brings all file to local
🔸 `git pull origin main ` // brings all changes from remote to local

### 🔶 Local to Remote

🔸 `git init ` // to initiate git in your folder
🔸 `git remote add origin(name) git-link ` // adds remote
🔸 `git remote remove origin ` // removes link remote/repository
🔸 `git remote -v ` // Used to verify remote
🔸 `git branch` // to check branch
🔸 `git branch -M main(new name)` // to rename the current branch
🔸 `git branch checkout -b new-branch-name ` // create and switch to new branch
🔸 `git branch checkout branch-name` // to change branch
🔸 `git branch -d branch-name ` // deletes a branch when on another branch
🔸 `git diff branch-name ` // gives differences between two branches
🔸 `git merge filename ` // merge current branch with other branch
🔸 `git push name (branch) ` // push project to github
🔸 `git push origin main`
🔸 `git push -u origin main ` // shortcut to push to same location

### 🔶 Modified & Untracked Files

🔸 `git add filename ` // adds file to stage
🔸 `git add . ` // adds all files to stage
🔸 `git commit -m "comment the change" ` // commit changes with a message
🔸 `git status ` // shows the sync status of local

### ERROR CORRECTION

🔸 `git reset` // reset all added files to previous form
🔸 `git reset filename` // reset added file to previous form
🔸 `git reset HEAD~1` // returns to one commit earlier
🔸 `git log` // logs all the commits with hash code
🔸 `git reset commit-hash-code` // resets to perticular commit
🔸 `git reset --hard commit-hash-code` // reset and show changes in vs code also

### FORK

// Makes copy of github repo in your account to make changes and contribute

### GIT COLLAB

Team Head Creates a project
Team Member forks the project, adds contribution and then requests pull request

</div>
</div>
