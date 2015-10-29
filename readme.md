## Interactivity && Graphics && Sound

### Due Date : October 6

### Goals:

1. See, Hear, Respond
2. Breakdown
3. Turning In
4. Read
5. Read More


#### 1. See and Hear
Combine Visual, Aural, and interactive elements. Completed projects will be projected and connected to the speaker system; unless requiring unique viewing/hearing hardware, for example: Oculus Rift, Leap Motion, etc. Completed projects can be infinitely evolving, directly responsive, performative, and so on.

#### 2. Breakdown
Before getting code dirty, draw/write out the bits and pieces of what you think you'll need. What are the components? How should they connect? Is there an order to events? 

#### 3. Turning In
First is to make your own repository of files and sync it to github. Then, Clone this assignment directory to your computer. From within the folder of the clone, use the terminal. 

Make a branch, replace _your-branch-name_ with something unique, rcsid, etc.

```bash
git branch your-branch-name
```
Checkout _your-branch-name_ so that we're working in that branch.

```bash
git checkout your-branch-name
```

Replace _remote-url_ with something like _https://github.com/shawnlawson/shawnmodule.git_ and _linked-folder-name_ with your name _shawnlawson_

```bash
git submodule add remote-url linked-folder-name
```

Then you'll need to add and commit.

```bash
git commit -a -m 'adding submodule'
```

You'll need to push your branch to the remote.

```bash
git push
```
From the github web interface for this assignment's repository you'll create a new pull request.

Base will be master, compare will be _your-branch-name_

Create the request. You shouldn't accept your own pull request. Someone else, me or another person, should review the request to make sure none of the other files in the repository were modified before accepting. Sort of like a checks and balances system. 

__Warning__ you can only push if you're a member of our organization. And, do not delete anything from the repository before pushing.
#### 4. Read
In all of these, ski[p,m] the Processing parts. 

_Programming Interactivity_, Chapter 5, This one is up to you: Object Oriented Programming, Pointers, References, and Arrays. When Are You Going to Use This?  -> page 157. 

_Programming Interactivity_, Chapter 6, This one is also up to you: Review of things we've done, OF tour, IDE's, setup, debugging. 

_Programming Interactivity_, Chapter 8, Graphics, Animation, Vectors. 

_Programming Interactivity_, Chapter 9, Pixel data. 

_Programming Interactivity_, Chapter 10, Sound. 

_Programming Interactivity_, Chapter 13, This one is also up to you: 3D. Or just the shader part on pages 520 - 529.

#### 5. Read More
A few more things to read are in the google drive. We won't have time to directly talk about them, but are good to think about. 