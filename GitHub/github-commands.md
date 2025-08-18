<div style= "width: 100%; background-image: url(assets/paper.jpg); background-size: contain;">

<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **GITHUB CHEATSHEET** 🔥🐦‍🔥

## Terms

- Local - Laptop
- remote - Github

## Workflow

> Github repo --> Clone --> changes --> git init --> git remote add --> add --> commit --> push

## Commands

| General Commands     | Usage                  |
| :------------------- | :--------------------- |
| cd ./perent/child    | Change Directory       |
| cd ..                | Return to parent       |
| mkdir directory_name | Create new folder      |
| clear                | Clears the terminal    |
| ls                   | list all elements      |
| ls -a                | shows all hidden files |

> - `git clone https://github.com/aanshik-dev/Example.git ` // brings all file to your laptop
> - `git status ` // shows the sync status of repo up to date

### MODIFIED & UNTRACKED FILES

> - `git add filename ` // to add file to stage
> - `git add . ` // to add all files
> - `git commit -m "comment the change" ` // commit changes with a message
> - `git init ` // to initiate git in your folder
> - `git remote add origin(name) git-link ` // adds remote
> - `git remote remove origin ` // removes link remote/repository
> - `git remote -v ` // Used to verify remote
> - `git branch` // to check branch
> - `git branch -M main(new name)` // to rename the current branch
> - `git branch checkout -b new-branch-name ` // create and switch to new branch
> - `git branch checkout branch-name` // to change branch
> - `git branch -d branch-name ` // deletes a branch when on another branch
> - `git diff branch-name ` // gives differences between two branches
> - `git pull origin main ` // brings all changes in local from remote
> - `git merge filename ` // merge current branch with other branch
> - `git push name (branch) ` // push project to github
> - `git push origin main
> - `git push -u origin main ` // shortcut to push to same location

### ERROR CORRECTION

> - `git reset` // reset all added files to previous from
> - `git reset filename` // reset added file to previous from
> - `git reset HEAD~1` // returns to one commit earlier
> - `git log` // logs all the commits with hash code
> - `git reset commit-hash-code` // resets to perticular commit
> - `git reset --hard commit-hash-code` // reset and show changes in vs code also

### FORK

// Makes copy of github repo in your account to make changes and contribute

### GIT COLLAB

Team Head
create a project

</div>
</div>
