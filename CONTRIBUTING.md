# Contributing guidelines


## Getting started guide

This section describes a tutorial for how to get started with developing course material for IN1910.

### Set up your environment
First of all you need to set up your environment so that you can build all the materials locally on your computer. The material is built using [jupyter-book](https://jupyterbook.org/en/stable/intro.html) which is an framework for building documents with computational content. This can be installed with python's package manager `pip`. First step would therefore be to set up a [python virtual environment](https://realpython.com/python-virtual-environments-a-primer/). We recommend that you set up a new environment every time you start a new project.

In this repository you will find both a `requirements.txt` file that you can install in a python virtual environment using
```
python3 -m pip install -r requirements.txt
```

### Building the book
Once everything is install you can build the book using the command
```
jupyter-book build -W book
```
There is also a `Makefile` in the repository that you can use, which has a target `docs`, i.e `make docs` will do "almost" the same thing.
This will take some time the first time you run it, because it will execute all the notebooks (and markdown files with executable content). It will then cache the results so that next time you run it, it will be much faster.

When the build is finished, you can view the page python opening the file `book/_build/html/index.html`. It is also possible to start a python server e.g
```
python3 -m http.server -d book/_build/html
```
and the open the url <http://localhost:8000> in your browser. Note that the `-W` flag in the build command will turn warnings into errors, which might make the build fail if there are any warnings. If you omit this flag (i.e run the command `jupyter-book build book` instead) you can build the book and see the output and maybe also sort out what is wrong.

### Pre-commit hooks
When developing content for the course there are set of style guides that you need to follow. These enforced through a set of [pre-commit hooks](https://pre-commit.com). You need to installed these hooks by first installing `pre-commit`
```
python3 -m pip install pre-commit
```
and then install the hooks using
```
pre-commit install
```
Now you can run the hooks on all the files using
```
pre-commit run --all
```
Note that once the hooks are installed, these tests will run on the files that you try to commit to the repo. If the hooks finds any mistake, they they will try to automatically fix then, in which case the tests will fail first and change the file so that it meet the style guide.
Try to add an extra newline to the README file, and try to add it to the repo (using `git add` and then `git commit -m "Add newline to README"`). The hooks should now see that the README file has too many newlines and remove the obsolete ones. Use `git add` again and you will see from `git status` that you have no files to be committed.

### Example - Add a word to the wordlist.
There is a Norwegian-English and English-Norwegian dictionary with common computer science words in the repo. You will now be given an exercise to add a new word to the dictionary. The dictionary is written in the file in `book/docs/info/dictionary.md`, but you should NOT edit this file directly. Instead you should edit the file called `wordlist.csv` which is found in the root directory of the repo. This is comma separated list with `Bokmål,Nynorsk,Engelsk,Beskrivelse`, but none of the words have a Nynorsk translation nor a description, so we have for example `feil,,bug,` which tells us that `feil` is the (Bokmål) Norwegian translation of Bug. Note also the there might be several translations of the same words. For example `feil,,error,` is another line.

The file `book/docs/info/dictionary.md` is generated from this csv file using the script `generate_wordlist.py` (also found in the root of the repo).
- Add a new word to the wordlist that is not yet listed in the wordlist
- Run the `generate_wordlist.py` script (for this you would also need to install `mdformat-myst`, i.e `python3 -m pip install mdformat-myst`)
- Create a new branch called `<your username>/add-word-to-wordlist` (where you change `<your username>` with your username)
- Add the changes to git and try to commit.

You will now see the hooks running, and you might see them failing. One hook that might fail is the spell checker. The spell-checker uses two different dictionaries; one Norwegian dictionary and one specific for the course. Most likely, you added a Norwegian word that is not in the dictionary, and which you should add to the Norwegian dictionary in the file `.cspell_dict_norsk.txt` (the file `.cspell_dict.txt` contains the English words for the course that is not listed in the general English dictionary that comes with the spell checker).

- Add the missing word to `.cspell_dict_norsk.txt`
- Add the files to the git repo and try to commit again

### Build the book to see the changes

- Build the book and see that your new word is found in the word list on the website

### Pull request process
You are now ready to push your branch to the remote repository and get feedback on your changes
- Push the branch
- Open a pull request to `main`

You should now see the continuous integration system running. This will try to build the book and run the pre-commit hooks. Make sure the checks from the continuous integration passes and ask for review.

- Assign one of the project maintainers as a reviewer


## Check List on Lecture Notes

The lecture notes were originally intended as *lecture notes*, but we now wish to formalize them somewhat.
Some of these points will be automatically checked by the pre-commit hooks, so please make sure to install the pre-commit hooks.


### Langauge

The current lecture notes are written in a very oral form, and we should try to make the language more formal
- Careful with abbreviations:
    - use “do not”, not “don’t”
    - use “let us”, not “lets”
- Remove references from “lectures last week”, and refer to chapters
- Remove colon (`:`) before presenting an equation or code.
- Fix typos, and improve formulations
- Edit the structure of sections when needed

#### Spell check
Please run the spell checker as a part of your pre-commit hooks. If there are words that are not part of the dictionary then you can add the word to the file .cspell_dict.txt

#### Norwegian - English dictionary
If you find words that we should include in the Norwegian-English translation dictionary then add those words to the csv file called wordlist.csv. This file should also eventually be populated with Norwegian nynorsk words as well as a short description of each word. Norwegian words can be added to the dictionary .cspell_dict_norsk.txt


### Consistency is Key
- Capitalise Python and C++ (not python and c++)
- Tabs with Python and C++ code: Priority after topic

#### Examples using Python
- Follow [PEP8](https://peps.python.org/pep-0008/)
- Follow [PEP257](https://peps.python.org/pep-0257/)
- Make sure all examples run

If you use the markdown directive:

\`\`\`{code-cell} Python

...

\`\`\`

Then the cell will by run when building the book. In this case you will see if there are any issues with the code in the rendered book.
If you use the markdown directive:

\`\`\` Python

...

\`\`\`

then the code will not run when building the book.

#### Examples using C++
- Run [clang-format](https://pages.github.uio.no/IN1910/IN1910_H22/docs/lectures/cpp/cpptools.html#formatting-your-code-with-clang-format) with Microsoft style on each code snippet:
```
clang-format -i --style=Microsoft *.cpp
```
- For naming conversions see [the core guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-naming)
- Compile and run the examples in a cpp file in order to make sure it works.

For Python, we run the pre-commit hook called [blacken-docs](https://github.com/asottile/blacken-docs) which verifies that the code is valid. We do not have any such tool for C++, so it is important to make sure the code is working. (We could consider making a workflow for this).

### Exercises within the lecture notes to check understanding
It would be good to add some small exercises alongside the lecture notes, similar to [this](https://realpython.com/python3-object-oriented-programming/#check-your-understanding). These exercises should be fairly small and to the point. You can use Hide/Show boxes similar to what is used in project 0 and project 1.

Also, think about exercises when reading through the lecture notes. If you come up with a good exercise that would be suited for a particular lecture, then write down the skeleton in a new issue on GitHub, and then you could get back to it later.


### References

Keep explanations short, and supply sources for further reading. Add references where needed, and replace all references to Wikipedia.

You can use:
- YouTube (lectures from other universities, conferences)
- Articles that are easy enough to read
- Books
- Documentation

Also note that UiO users have access to several books online and it is good if you can provide links to those, see e.g [the list on GitHub pages](https://pages.github.uio.no/IN1910/IN1910_H22/docs/info/curriculum.html). In general, make sure the sources are reliable and trustworthy.
