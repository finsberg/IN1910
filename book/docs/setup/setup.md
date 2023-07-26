# Installation instructions

We recommend everyone to download and install [Anaconda](https://docs.anaconda.com/anaconda/install/index.html). You are of course free to download and install python and the third party packages in other ways.
Note that if you install anaconda, then you will end up installing a lot more packages than you need to. In you don't want that, then one alternative is to install [Miniconda](https://docs.conda.io/en/latest/miniconda.html), download the [following environment file](https://gist.githubusercontent.com/finsberg/95b88d7e039a76466ba667c3c9d2850e/raw) that contains all the necessary package and install them in a [conda environment](https://conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html#creating-an-environment-from-an-environment-yml-file) with the command
```
conda env create -f environment.yml
```
This will create a new environment called `IN1910`, see [Virtual environments](virtual-environments) for more info about virtual environments.

## Installing third party packages with conda

For the course IN1910 you need to install the following software:

- Python version 3.8 or newer
- [SciPy stack](https://www.scipy.org/stackspec.html)
- [pytest](https://docs.pytest.org/en/stable/getting-started.html)
- [pybind11](https://pybind11.readthedocs.io/en/stable/)

This can be installed using the [Anaconda distribution](https://www.anaconda.com/distribution/#download-section) which is recommended. There are also other options to install [python](https://realpython.com/installing-python/) depending on your operating system. You may also consult the [guide from IN1900](https://www.uio.no/studier/emner/matnat/ifi/IN1900/h18/ressurser/installering.html).

(virtual-environments)=
### Virtual environments
The main purpose of a virtual environment is to create an isolated environment where you install all your dependencies. Say that you are working on a project where you need a specific version of a package (say numpy). First thing you might wonder is *why would you need a specific version of numpy?*. Well, numpy evolves all the time. New functionality is added and some functions might be deprecated and removed. If you are working on a large code base that depends on some old numpy functionality that is removed in the most recent version, then you can either try to upgrade the package to support the most recent version of numpy, or you can just stick to an older version.

Say now, that you are starting on a completely new project, and you want to make use of some brand new functionality in numpy. How do you handle that, without breaking the existing project? This is where virtual environments comes to play.

When using conda, it is easy to have multiple [conda environments](https://conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html#creating-an-environment-with-commands) which are virtual environment within the conda ecosystem. To create a new environment, simply do
```
conda create --name IN1910
```
This will ask you to confirm that you want to create a new environment called `IN1910`. Type `y` and hit enter. To activate this newly created environment you type
```
conda activate IN1910
```
Now you can install a package that you need, e.g
```
conda install numpy
```
To deactivate the conda environment you can use the command
```
conda deactivate
```

#### Troubleshoot virtual environments
Once you have activated the virtual environment using the command
```
conda activate IN1910
```
you can verify that you have successfully activated the environment.
Do do so you can check which `python` you are using by executing the command
```
python -c "import sys; print(sys.executable)"
```
In my case the result was `/Users/henriknf/miniconda3/envs/IN1910/bin/python`. You will probably not have the exact same results, but you should at least see `IN1910` in the path to python.
If you don't see that then the environment is not properly activated.
In this case try to deactivate the conda environment a few times and activate again, i.e
```
conda deactivate
conda deactivate
conda deactivate
conda activate IN1910
```
If you still don't see `IN1910` in the path to the `python` executable, then reach out to one of us or ask fellow student.

## Git
Please consult [GitHub docs](https://docs.github.com/en/get-started/quickstart/set-up-git) for a very good guide on how to set up git.
You need to first install Git locally on your laptop. Next you need to make sure that you are able to [connect to Github using either HTTPS or SSH.](https://docs.github.com/en/get-started/quickstart/set-up-git#next-steps-authenticating-with-github-from-git)

## Choosing an editor

When working with code development you need a proper code editor.
Some popular choices includes
  - [Visual Studio Code](https://code.visualstudio.com) (This is the one that will be used by in lectures)
  - [Sublime Text](https://www.sublimetext.com)
  - [Atom](https://atom.io)
  - [Emacs](https://www.gnu.org/software/emacs/)
  - [Vim](https://www.vim.org/download.php)

For a more extensive list, please checkout the [Stackoverflow survey from 2021](https://insights.stackoverflow.com/survey/2021#section-most-popular-technologies-integrated-development-environment)


## C++
Please see the [C++ installation guide](cpp_compiler.md)
