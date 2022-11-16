.PHONY: clean clean-ipynb clean-pyc clean-build docs help upgrade
.DEFAULT_GOAL := help

define PRINT_HELP_PY_SCRIPT
import re, sys

for line in sys.stdin:
	match = re.match(r'^([a-zA-Z_-]+):.*?## (.*)$$', line)
	if match:
		target, help = match.groups()
		print("%-20s %s" % (target, help))
endef
export PRINT_HELP_PY_SCRIPT

help:
	@python -c "$$PRINT_HELP_PY_SCRIPT" < $(MAKEFILE_LIST)

docs: ## Build book
	jupyter-book build book
	cp requirements.txt book/_build/html/.
	for lecture in L01 L02; do \
		cp -r book/docs/slides/$$lecture/figures book/_build/html/docs/slides/$$lecture/ ; \
	done
	touch book/_build/html/.nojekyll


show:  ## Open index page
	open book/_build/html/index.html

clean: clean-build clean-pyc clean-ipynb ## remove all build, test, coverage and Python artifacts

clean-build: ## remove build artifacts
	rm -fr book/_build/

clean-pyc: ## remove Python file artifacts
	find . -name '*.pyc' -exec rm -f {} +
	find . -name '*.pyo' -exec rm -f {} +
	find . -name '*~' -exec rm -f {} +
	find . -name '__pycache__' -exec rm -fr {} +

clean-ipynb:  ## remove notebook artifacts
	find . -name '.ipynb_checkpoints' -exec rm -fr {} +
	rm book/docs/slides/L*/*jukseark.ipynb

clean-pytest:  ## remove pytest cache
	find . -name '.pytest_cache' -exec rm -fr {} +
