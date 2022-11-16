---
jupytext:
  formats: md:myst
  text_representation:
    extension: .md
    format_name: myst
kernelspec:
  display_name: Python 3
  language: python
  name: python3
---

# Version Control with Git

In this lecture we will cover version control with Git. These lecture notes will go into what Git is, and simple examples of use. The accompanying exercises will require you to use Git to track and store your code.


## References

Learning Git, like most aspects of programming, is best learnt by doing it yourself. In this course, you will learn the basics of using Git and GitHub by using it for your assignments and hand-ins. In this lecture, you will learn the basics, and as the course goes on, you will learn more and become more proficient.

However, if you want a different introduction to Git than these lecture notes, or you want something in addition, there are *a lot* of resources for learning Git online. And we will list some here.

Perhaps the best and simplest resource available is the [GitHub guides](https://guides.github.com). Here you will find the [Git Handbook](https://guides.github.com/introduction/git-handbook/) that contains a reference all the basic Git commands as well links to more resources. The [Understanding the GitHub flow](https://guides.github.com/introduction/flow/) section is a short but great read to learn the basic concepts about how developers use GitHub in their workflow. Finally there is a simple [Hello world](https://guides.github.com/activities/hello-world/) project that we recommend all students to check out, if you are a complete newbie to Git or GitHub.

Another very good resource is from one for GitHub's competitors [Atlassian](https://www.atlassian.com/git).

If you want a more interactive tool, you can also check out <https://learngitbranching.js.org>.

If you want to go more in depth, or have a more extensive reference work, the book *Pro Git* by Scott Chacon and Ben Straub is released under a [Creative Commons BY-NC-SA3.0 license](https://creativecommons.org/licenses/by-nc-sa/3.0/?utm_source=www.domtail.com), meaning you can download it for free. The 2. edition was released in 2014, and on the book's website you can download it as a pdf as well as some common e-book formats (epub, mobi). The book itself is very extensive, being over 500 pages. However, it starts of fairly easy, and goes into more technical details towards the end, so reading the first few chapters can still be a good introduction to git.

```{figure} ../../figures/progit.png
---
width: 300px
name: progit
alt: progit
---
Pro Git Book website: https://git-scm.com/book/en/v2
```

Another very good alternative it the book called [*Version Control by Example*](https://ericsink.com/vcbe/vcbe_a4_lo.pdf) which also touches upon the history of version control as well as other version control system than git.

At this point we should stress that these resources are simply offered as an alternative, or in addition, to the lecture notes, and we do not expect you to use them unless you want to.


## Why version control?

Imagine you have a new software assignment, with a three week deadline. You start working and things are progressing nicely, things are working well and you are happy with your code. Entering the last week, all you have left is to refactor your code and add some small final changes. However, in this process, things suddenly *stop* working. What happened, and what do you do? Some change you did while refactoring probably messed something up, but you cannot undo everything you have changed, can you? This is just one case where *version control* would be useful. Giving you the option to "go back in time" in your code.


```{figure} ../../figures/phd_final.gif
---
height: 300px
name: phd-final
---
Source: Taken from [www.phdcomics.com](http://phdcomics.com/comics/archive_print.php?comicid=1531). Created by Jorge Cham
```

Today we will discuss version control systems (VCS), and *Git*, a tool to automate version control. Simply put, VCS is a crucial tool for any software developer, and the bigger a project you are working on, the more important it is.



The main idea of VCS is very simple, we make regular "backups" of our code at different times, enabling us to look at how the code looked earlier, or in extreme cases, revert the whole codebase to an earlier time. There are many tools for automatic backup of your machine, and many tools have it built in. Dropbox for example has checkpoints of your files built in, which can be very helpful at times. The tools we will discuss today however, are especially built for software development.


## Benefits of version control

Some benefits of version control are
* Backup of files in case of computer crashes etc
* Make it easier to see which changes introduced an error
* Let's the user undo bad changes and revert to working copies
* Great for collaboration, and let's several people contribute to the same project
* Allows for *branching* of code, to test new ideas or make different versions of the code
* Accountability. Version control lets you see who did what


### Different Version Control Systems

A VCS is any framework that allows you to keep track of your project over time, and stores revisions. The simplest form is a local one, where the entire file history is stored locally on your computer or network.


```{figure} ../../figures/local_vcs.png
---
width: 300px
name: local-vcs
alt: local vcs
---
A local VCS. Source: Chacon & Straub, ProGit (2014)
```

There are two problems with using a local VCS. The first is that there is no backup in case of a computer crash or failure. In addition, most programmers do not work on projects by themselves, but often need to pass code back and forth, or have the options of several programmers working on the code simultaneously. A local VCS does not handle such collaboration too well.

One way to deal with these challenges is to use a *centralized* server to keep track of the version history. Different users can read out specific versions of files, work on the code and upload their changes to the server. This makes collaboration between programmers easy. Admins and team leaders can also monitor the server and give people the rights to alter the code they are working on. It also has the benefit that if any persons laptop or computer crashes, it doesn't impact the whole system, only their last changes they haven't uploaded yet. However, the central server is still a single point of failure, and should be properly backed up—and if the server is down for a while due to maintenance or issues, working becomes hard for the team, and efficiency drops.

```{figure} ../../figures/centralized_vcs.png
---
width: 300px
name: centralized-vcs
alt: centralized vcs
---
A centralized VCS. Source: Chacon & Straub, ProGit (2014)
```

The kind of VCS we will be using is called a *distributed* VCS. Like the centralized system, we will also interact with an external server to do backups and collaboration. The difference is that with the distributed VCS, every user stores a complete copy of the entire project history. This gives additional safety, as every user has a complete backup. It also gives efficiency, as users can access the whole project history, even offline, and only have to push or pull the changes in code. The only downside is use of space, as we are storing the same information multiple places. However, most software projects take little space, and so this is of little issue.

```{figure} ../../figures/distributed_vcs.png
---
width: 300px
name: distributed-vcs
alt: distributed vcs
---
A distributed VCS. Source: Chacon & Straub, ProGit (2014)
```


## Enter: Git

There are *many* different version control softwares to choose from today. The one we will be using for IN1910 is called *Git*. We choose *Git* because it is highly popular and sees much use, especially in open source development and scientific programming. Secondly, it is open source and free, which is always nice. In the "real world", you might be part of a team or scientific group, in which case you should use the same VCS as them. However, other common VCS, such as Mercurial and Bazaar, also look a lot like Git. So knowing Git, you will most likely be able to pick them up with little issue.

So where does Git come from? It was created by Linus Torvalds in 2005 to be used for the development of the Linux kernel. The Linux development team had been using a proprietary software called BitKeeper, but there was a falling out. As a result, Linus decided to develop his own software to take its place. (That was oversimplifying the story considerably).

One reason Git grew into popularity so fast was that it was precisely that, *fast*. It is so fast you rarely have to wait for it at all, even when working on huge projects (like the Linux kernel).

### Git Commits

When you work with Git, you will edit and work with your files as normal. At regular intervals however, you make *commits*. These commits are "snapshots" of your project files that will be stored in the projects history. Over time you get a long chain of these commits. When looking at your project through your normal file tracker or text editor, you only see your current version of the software. To store the history, Git creates a *hidden* `.git`-directory. You should ignore this hidden directory and all its files, and never access or edit them manually, as this will mostly break your version control. If you want to look at or access older commits, you do some simple git-commands.


```{figure} ../../figures/snapshot_filestream.png
---
width: 500px
name: snapshot-filestream
alt: snapshot filestream
---
Source: Chacon & Straub, ProGit (2014)
```

The entire project, including the project history stored in the .git folder, is referred to as a *repository*. Typically, we create a new repository for each new software project we do.

A *commit* typically includes all changes to your project files since your last commit. This includes edits to files, but also creation and deletion of files. If you delete a file from your project, older commits will still contain that file. Thus, when making new commits, we only ever *add* things to our project, we never remove it. What happens in git, stays in git. In addition, each commit is named after a hash of the complete project history thus far, which makes the project history tamper proof. If you go in and try to change the history, the hashes will no longer match.

In this sense, Git is quite like a [blockchain](https://en.wikipedia.org/wiki/Blockchain). Strictly speaking, Git doesn't really use a blockchain, but it is based on Merkle trees, which also underlies blockchains. You can read [this Stack Overflow question](https://stackoverflow.com/questions/46192377/why-is-git-not-considered-a-block-chain) if you are curious.




## Installing and Setting up Git

Please consult the [setup instructions](../../setup/setup.md) for information about how to set up git correctly.

After you have installed Git, you need to configure it before we use it. Specifically we need to add your name and email to git, so that changes you make your and others repositories are marked to you. This is quite simple, just open a terminal and write
```
git config --global user.name "John Doe"
git config --global user.email johndoe@example.com
```
Once you have run these two commands successfully, you are ready to use Git! You can check out [first time git setup guide](https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup) for more configurations.

### Choosing a remote server

Git is a piece of software you install on your computer and use through the terminal. You can choose to use Git only locally on your machine, and it will work nicely. However, a major benefit of Git is that it is distributed VCS, and so we will want to also copy our project repository over to an external server as well. Here there are many third party services to choose from, but the two major ones for Git repositories are Github, Bitbucket and Gitlab. All of them provide free accounts, and paid accounts with more functionality. They also provide benefits for students, so signing up with your student email is recommended.

For this course we will use UiO's own Github server. This will behave and look quite a lot like the official Github server [https://github.com/](https://github.com/). You do not need to create a user for the UiO github, you simply log in with your UiO user and password.

* [https://github.uio.no](https://github.uio.no/)

If you also want to create a user on github.com, you are welcome to do so. However, the project work will be carried out and handed in via github.uio.no. Note however that some functionality (which you will see already in project 0) is not available on UiO's own GitHub server yet.


### Getting a repository

Now that you have Git, and a Github user, we need to get our hands on a git repository to play around with. There are two alternatives:
* Making a brand new one
* Copying an existing one

To copy an existing one, you need to first find one. For example the IN1910 repository. You can then copy the repository to your machine by using the `git clone` command and adding the url of the repository.
```
git clone https://github.uio.no/IN1910/IN1910_H21
```
This is made easier by using the "Clone" button on any repository website. You now get a local copy of the entire repository on your machine. This is for example one way to download the course material, although we recommend to just use the Github pages directly.

When cloning a repository somebody else has made, you get a local copy of it. When the original owner makes a new change to the online repository, you can get these changes into your own copy by doing a `git pull`-command, more on this later. For the IN1910 repo, this means every time we add new lecture notes or assignments, you can pull these changes down to your machine with a simple command.


### Creating a new repository

Playing around with the IN1910 repository isn't the best for learning, so let us instead create a new repository from scratch. This can either be done locally on our machine, or through Github.

### Creating a repository locally

To create a new repository locally, first create a new folder for your project, then navigate to it in a terminal, and then run the command `git init`. The name of your repository is the name of the folder, so choose a good one. As an example, let's say we want a repository to track exercises we do on the website [projecteuler.net](https://projecteuler.net/), so we call our project `euler`. We would do as follows
```
mkdir euler
cd euler
git init
```
Note that we are creating an empty repository here. If you already have a project folder filled with code, you can start a repository from it using `git init`.

### Creating a repository through Github

An alternative is to make it through Github. In which case, you just go onto Github. Click the `+` sign and choose "New Repository". You will come to a page that looks like the following:


```{figure} ../../figures/repo_creation.png
---
width: 500px
name: repo-creation
alt: repo creation
---
Creating a repository at GitHub
```


Here we need to enter the name of the project, and an optional short description. We can choose to make our repo public, in which case it can be accessed by everyone online (or everyone with a UiO user for github.uio.no), or private, in case only the people we explicitly give access can see it. If you want to get more out of your regular GitHub account you can apply for a [student develop pack](https://help.github.com/articles/applying-for-a-student-developer-pack/).

Finally we can add a README, a `.gitignore` and a license. For now we do want the README, as it makes things practical. We don't use the `.gitignore` for now, we will talk about it later. We also leave the license blank.

Once you have made your repo on Github. You can clone it down to your local machine
```
git clone https://github.com/jvbrink/euler
```
In which case, git will make a folder called `euler` which we can access.


### Adding files to your project

We now have a folder called `euler`. We can treat this as a completely normal folder on our computer, meaning you can move files into it, or create new files within it. Say we now add a file called `problem1.py`, which solves the [first Project Euler problem](https://projecteuler.net/problem=1).

When you want to include new files into your project history through a commit, you first have to *add* them, this is also known as "staging" the files or changes. When you do a commit command, all staged changes are now added to the project history.

```{figure} ../../figures/three_states.png
---
width: 400px
name: three-states
alt: repo creation
---
Source: Chacon & Straub, ProGit (2014)
```

We can at any time check the current status of the git repository by running
```
git status
```
which now tells us
```
On branch master
Your branch is up to date with 'origin/master'.

Untracked files:
  (use "git add <file>..." to include in what will be committed)

	problem1.py

nothing added to commit but untracked files present (use "git add" to track)
```
The first lines tells us there is nothing new on Github that has been added after we cloned our repository (you won't see this if you only have a local repository for now). Next it tells us that there is an *untracked* file, which is the new file we created.

If we want to commit our new solution, we will therefore first have to add it
```
git add problem1.py
```
or simply
```
git add .
```
which adds everything in the folder and sub-folders. Doing this is very practical, but perhaps we are storing files in our folder we don't want to enter into the project history (because they should only be stored locally, and don't need backups), then doing `add .` would add those too. The solution is to add a file called `.gitignore` in our project folder. This file contains a list of files that should not be added into git. There is a website, [gitignore.io](https://www.gitignore.io/), that let's you autogenerate a gitignore file based on your system and programs you used. If you are starting a new repository, it is helpful to take the 30 seconds it takes to make a proper gitignore file. Useful things to add into gitignore.io is your operating system, your text editor, and the programming languages you are using for your project. This will keep your public repo looking nice and clean.

Note that `git add .` will add everything in that is not in your `.gitignore` file. If only want to add the files that have already been added, i.e you only want to update the existing files you can use the command `git add -u .`.


### Your turn: Making a .gitignore file

Create a file called `.gitignore` (exactly that), go to the website [gitignore.io](https://www.gitignore.io/) and fill in your OS, your editor, Jupyter notebook, and Python. Copy the output you get from the website into your newly created file and save it. Then *stage* it by doing `git add .gitignore`.



### Making a commit

To make a commit, we simply use the command `git commit`. If you just run that command, it will open a text editor for you to enter a commit *message*. A commit message is a short text, usually a sentence, that describes the changes you have performed since the last commit. All commits should have commit messages, because it allows others, including your future self, track changes to the project over time. A large software project will usually grow to thousands of commits over time, so having some explanations can really help. The messages also makes it easier to see where possible bugs were introduced.

Instead of letting git open an editor for you, you can write your commit message straight into your commit command using the `-m` flag.
```
git commit -m "Solved problem 1 using Python."
```
And that is it. We have stored a snapshot of our project.

### A note on adding and editing files

All new files you create will need to be added using `git add`. However, most of the time you are simply editing existing files. We can for example now go in and change our `problem1.py` around a bit. If we have an edited file, this will also show up in `git status`. Let us also add a `problem2.py` for illustration. The status command now gives us (and some additional information we removed for readability)
```
Changes not staged for commit:
	modified:   problem1.py

Untracked files:
	problem2.py
```
To stage both the changes, and the new file, we can use `git add .` to include both at once.
```
git add .
git commit -m "Solved problem 2 using Python."
```
This commit will now add `problem2.py` and the changes to `problem1.py` simultaneously.

### git commit -am

If we only want to include changes to existing files, but we have not made any *new* files. We can use the `-a` flag to the commit. That way, we don't have to keep running the add command for every commit, we only do it when we are actually adding new files. A typical commit command can then look like this:
```
git commit -am "Added support for reading .png images to the scan module."
```

We have now made a repository and made two commits to it. We can use `git log` to get out a report of commits in a chain
```
git log
```
Giving
```
commit 08b79fde10ad4ad7aed89881aa44275c175af509 (HEAD -> master)
Author: jvbrink <jonasvdbrink@gmail.com>
Date:   Thu Aug 9 12:04:38 2018 +0200

    Solved problem 2 with Python

commit 3fd2c980dfe696a8f42bc414e260721e11a7f48e
Author: jvbrink <jonasvdbrink@gmail.com>
Date:   Thu Aug 9 11:52:42 2018 +0200

    Solved problem 1 using Python

commit 0c2dd72daaa5aa3496a036611d52b57193e83f3a (origin/master, origin/HEAD)
Author: Jonas van den Brink <jvbrink@users.noreply.github.com>
Date:   Thu Aug 9 11:17:56 2018 +0200

    Initial commit
```
The most recent commit comes first, and then older ones below it. The time of the commit, and the person commit is also given. Each commit is named by its *hash*. In addition we have some info, `HEAD` is a concept in Git, it is pointing at the latest commit (but can be moved around if needed). Note that the `origin/HEAD` is still at our initial commit, this is because our changes so far have only been local, and `origin` is the name of our copy of the repository on github. Let us see how to fix this.

```{admonition} Pro tip: Committing only a part of a file
:class: tip
Sometimes you may have multiple changes to a file, but the changes might belong in different commits. To add only part of the file to the staging area you can use `git add -p`. This will
open and interactive window and show you the `git diff` of a section with a question `(1/2) Stage this hunk [y,n,q,a,d,j,J,g,/,e,?]?`. In this case you see that there are two sections (or hunks) and you are looking are the first one. Type `y` to include it `n` to not include it or `?` to see more info.

Similarly, if you want to discard changes to only parts of a file you can use `git checkout -p`
```

## Interacting with Github

We will now start interacting between our local repo and Github. The server (be it Github, or something else) is called the *origin* in Git-lingo. And so as you might have already seen in your `git status` messages, we see references to *origin* quite often.

To do the next steps, our repo must be coupled to Github. If you created your repo via the website and cloned it, they are already linked. If you created it locally using `git init`. You need to couple them together manually. To do this, first go to Github and create a new repository there as normal, but do *not* include a README, gitignore or license.

Then you can run the following command to couple it to the online repo
```
git remote add origin <URL>
```
You can verify the new remote URL using
```
git remote -v
```
Then finally, push everything up using
```
git push origin master
```
I prefer starting new repos on the website, then cloning them down, to avoid having to set the origin manually. But this is just personal preference.


### Pushing and Pulling

The two main commands you need to interact between your locally copy of the repository and the online one, are `push` and `pull`. Here `push` means you are copying commits you made locally up to the origin. While `pull` means you are copying commits that have been pushed to the online repo down to your local machine.

When we write `git status` in our euler project now, we get a message (unless you already pushed your commits)
```
Your branch is ahead of 'origin/master' by 2 commits.
```
This message is telling us we (meaning our local repo), is two commits ahead of the version on Github. To remedy this we push our latest changes. Run the command
```
git push
```
And you will be prompted for your username and password. This ensures no one else can push things to your repository. If you find it tiring to write your username and password all the time you can [cache your GitHub credentials in Git](https://docs.github.com/en/get-started/getting-started-with-git/caching-your-github-credentials-in-git). An alternative to this is to [set up SSH authentication ](https://docs.github.com/en/github/authenticating-to-github/connecting-to-github-with-ssh)

Pushing is important, because it is what ensures there is an external backup of your project. If you only do commits, and no pushing, and your computer is lost or broken, there goes all your hard work. If you have committed *and* pushed it, then you have a backup you can clone to a different machine. In addition, if you are sharing your code with others, then they will only get the changes you have made once you have pushed it. Because of these two things, we push often. You don't have to push after every single commit, but it is a good habit to push at least at the end of every coding session.


```{figure} ../../figures/in_case_of_fire.png
---
width: 250px
name: in-case-of-fire
alt: in case of fire
---
A common joke in the Git world. Getting your work to safety requires first a commit to store your last changes, and then a push to get your newest commits to the external sever
```

Pulling is not as much used if you are working on software alone, as it is used for copying changes others have contributed to a repository down to your local machine. But say for instance you are collaborating on a project with a friend, and your friend pushes a new piece of code you want to work on. Then you would do a
```
git pull
```
and the changes would be entered into your local repository.

```{admonition} Pro tip: Pull = Fetch + Merge
:class: tip
If you work on a project where your partner have pushed out changes to GitHub and you execute the command `git pull` (or `git pull origin master`), the changes from your partner will first be fetched (downloaded) from GitHub and then merged into the branch you are working on. In other words, `git pull origin master` consist of first executing the command `git fetch origin master` and then `git merge origin/master`. If you only want to view your partners changes without merging you can do `git fetch` (or `git fetch origin master`).
```


### How to test pushing and pulling on your own

We will go more in detail on collaborating through Git at a later time. But for now, let us show you an easy way you can "fake" being to two people collaborating just to learn some git—this is not something you will actually do when working with *git*. It is just a way to illustrate how it would work. To do this I simply clone my repository from Github once again, but place it in a different location on my machine.
```
mkdir git_collab_example
cd git_collab_example
git clone https://github.com/jvbrink/euler
```
I now have to copies of the same repository. One stored in my home directory, and one stored in a subfolder of my home directory. These two copies do not know the other one exists, and so for all intents and purposes they could just as well be on two different machines.

If I make changes to one of them and commit it, it won't show up in the other one by itself. However, I can do a *git push* in the one with the changes, and a *git pull* in the other, and they will both be up to date. This is because the push command sends the changes to the github server, and the pull command pulls down the new changes to the other repo. Imagine that these two repos were located on different machines, this would be a way for two colleague could work on the same code together.

The best way to *actually* learn how to collaborate in git is to find a partner and just try it out, and this is what we will be doing in the project work of the course.


### Git Forking

So far we have seen how we can *clone* a repository from Github. When we do this we get a local copy of it, and you can do this with any public repository found on Github, Bitbucket and similar pages. This means for most open source code projects, you can clone their repo and instantly have access to the source code, documentation and the like. In fact, many open source code projects share their code this way, making you first clone the repo and then build or install the software through some additional steps.

When you clone somebody else's repository, you can make local changes to it, but you won't be able to push any of those changes back to their online repository. This makes sense, it wouldn't work very well sharing code openly, if anybody could start messing with that code. However, you can instead link your local repository to a new public repository which you own. We call this process *forking*, and it works quite well. If you find some openly available software project you want to build on or modify in some way, you just make your own personal fork of it. Github makes it very easy to fork any repository, if you are logged in and looking at a repository, there is a "Fork" button, which automatically creates a new repository on your user from the other one, which you can then clone down to your local machine.

```{figure} ../../figures/github_forking.png
---
width: 400px
name: forking
alt: forking
---
You can easily Fork existing projects to build on, extend or modifying existing code
```

### Git Branching

Another crucial feature of git, at least for large projects. Is that you can make *branches* in your code. A branch is exactly what the name implies, a diverging version of the code. We can make branches for several reasons:
* For testing purposes
* Supporting different versions of the same code at the time
* For developing new features without disrupting the main code
* Doing crazy things that might break the code
* Bug fixing

To make a new branch you can do the command
```
git branch <new_branch_name>
```
Let's say we make one called `testing` for example. The situation is now as shown below:

```{figure} ../../figures/making_a_branch.png
---
width: 300px
name: making-a-branch
alt: making a branch
---
Source: Chacon & Straub, ProGit (2014)
```

Note that our original branch is called *master* (although it should actually be called [main](https://github.com/github/renaming)). When we start a new repo it only has the master branch. The new branch is called testing, and "HEAD" is where we are currently at. Because the HEAD is at master, if we make a new commit, it will be entered into the master branch, not the testing branch. If we instead want to change the testing branch, we have to move the head with
```
git checkout <branch_name>
```
Note that branches can diverge in commits, this is sort of the whole point of branches. We can then jump between the branches using `checkout` as needed.

```{figure} ../../figures/branching.png
---
width: 300px
name: branch
alt: branch
---
Source: Chacon & Straub, ProGit (2014)
```

Say we have made a branch to develop a cool new feature without disrupting the master branch others are also working on. Once we are happy with our code, we need to *merge* our branch back into the master branch.

```{figure} ../../figures/merging.png
---
width: 300px
name: merge
alt: merge
---
Source: Chacon & Straub, ProGit (2014)
```

To merge branches we want to be on the branch we want to keep (typically the master branch), and do the command
```
git merge <branch_name>
```
So once we manage to solve issue 53 in the image, we would do
```
git checkout master
git merge iss53
```
and that would be that.

Note that to merge branches, git tries to automatically understand what code to keep. If both branches that are to be merged has performed changes to the *same code*, this can be a bit tricky. In this case we get what is called a *merge conflict*. Which we have to resolve manually, meaning we need to choose which parts of the code to keep, and which to discard. Your first proper merge conflict will probably be a stressful situation, but just remember to keep calm and ask for help from your local git guru if needed.


### Merge requests and Pull requests

Another useful feature are merge and pull *requests*. Often when working in a software team, there is a team leader that is responsible for managing the big picture view of the whole codebase. The different developers on the team handle different tasks, and often do their development in separate branches of the main code. Once they finish a task, instead of simply merging it into the master branch, they make a *merge request*. This request is automatically sent to the team leader, who can then review the changes to be merged. After reviewing they can either accept the request, in which case the merge happens, make additional comments or requests to be carried out before the merge is acceptable, or they can outright deny the request. Pull requests are basically the same thing, but for pulling a commit into a repository. If you for example find and solve a big in an open source project you find online, you don't have *write access* to that repository, so you cannot actually push your changes. Instead you can make a pull request for the owner of the repo, and they can either accept or deny. If they accept, they get the changes you made into their project.

Linus Torvalds, the original creator, and currently principle developer of the Linux kernel, is sort of notorious for being quite harsh when it comes to pull requests—he will only accept good code, and if you produce a pull request of bad code he will let you hear it. This makes him a bit unpopular in some circles.


## Taking a step back

We have just covered a lot of different aspects of Git, and mentioned a lot of things you might not even use that much in IN1910. If it is all a bit overwhelming right now, don't worry. You will get hands on experience doing the weekly assignment.

The most important commands are
* `git clone <URL>`
* `git add .`
* `git commit -m "..."`
* `git push`
* `git pull`

If you know how to use these commands, you can probably get through IN1910 just fine. Other commands that are useful in the "real world", are branching, merging and tagging.


### Commit often!

For Git to be useful as a version control system, and not just a online backup, it is important to commit often. The more often you commit (within reason), the easier it is for both others and your future self to understand how the project changed over time, and exactly where potential errors occurred.

Each commit should also also have a *commit message* that explains the changes made. The commit message should be a single sentence, and should explain exactly what you did in the code itself, to see that people can always check out the commit log. Instead, your commit should explain the big-picture of what you were trying to accomplish. Did you write a new module? Add new functionality? Fix a bug? And so on.

In an ideal word, a commit should revolve around a single concept, sort of like a paragraph in a text. This means you should commit once you finish tackling a given problem, and started working on something else. If you are writing a commit message and see you are writing "Did A and B and C" and these are completely different tasks, then you should probably have made three separate commits. If you have already commit and done some more changes you feel should be part of that commit, you can *amend* that commit by doing
```
git commit --amend
```

The bigger a software project, the more important good commits and messages are. For assignments in this course, they are probably not that important, but we are trying to learn good practices, and so you should strive to make at least decent commits.


```{figure} ../../figures/xkcd1296_commit_messages.png
---
width: 500px
name: xdcd-git
alt: xdcd-git
---
Source: [XKCD #1296](https://xkcd.com/1296/)
```


## Best Practices for Scientific Computing

Let us wrap up this lecture by looking back at the paper mentioned during the first lecture, [*Best Practices for Scientific Computing*](http://journals.plos.org/plosbiology/article?id=10.1371/journal.pbio.1001745) by Wilson, et al. Many of them cover good use of Git.

The most relevant point, which explicitly talks about using VCS in the first place

3. Make incremental changes
    * (a) Work in small steps with frequent feedback and course correction
    * (b) Use a version control system
    * (c) Put everything that has been manually created in version control

In addition, the following points are very relevant:
5. Plan for mistakes
6. Optimize software only after it works correctly
8. Collaborate

Using VCS is, by its very nature, planning for mistakes. When optimizing code, it is very easy to break some functionality, and so having good revision control is crucial to refactoring and optimizing code effectively. Lastly, collaboration on code should be, and very often is, done through *git* or similar tools. By collaborating through git, it is a lot easier to track changes over time, see who made what changes, and all revisions are accessible. This is *a lot* better than just emailing code back and forth—which many scientists do!
