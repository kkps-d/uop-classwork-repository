# Tech Debt

## CI Tool
- Github Actions

## VScode Extensions
- [Python](https://marketplace.visualstudio.com/items?itemName=ms-python.python)
- [PyLint](https://marketplace.visualstudio.com/items?itemName=ms-python.pylint)
- [Pylance](https://marketplace.visualstudio.com/items?itemName=ms-python.vscode-pylance)
- [VS Live Share](https://marketplace.visualstudio.com/items?itemName=MS-vsliveshare.vsliveshare)
- [VS Code Github Actions Installation](https://marketplace.visualstudio.com/items?itemName=github.vscode-github-actions)
- [Git History](https://marketplace.visualstudio.com/items?itemName=donjayamanne.githistory)

## Installing pipenv

1. Install `pipenv`
    - `pip install pipenv==2023.3.20`
2. Once `pipenv` has been installed, switch to the virtual environment shell
    - `pipenv shell`
3. Install the required packages
    - `pipenv install`
4. Later, when running our programs, always run `pipenv shell` before running the python file. 
    - Also, do not use the `play` button in VSCode. Run the python file using `py main.py`

## Unit Tests (?)

## Additional Tools

VSCode

## Processes
- Create a UML diagram with the classes
- Always create a new branch when working on something
    - Not necessarily have to create new branches for every new feature 
- Do pull requests instead of committing straight to main
    - Code reviews are part of this
- Do pair programming when tackling tougher stuff

## Practices
- common commenting
- [Type hints](https://docs.python.org/3/library/typing.html)
- clear and concise naming conventions
    - use camel case `functionName`
- avoid magic numbers
- avoid code redundancy by reusing them
- when declaring public variables in python, use "_publicVariable"

## Bugs we experienced

pipenv shell will not work if you use microsoft store python so make sure to download python from the website.
If you decide to use vs code and need to download python, the automatic file path will be for microsoft python. To change this and use python that you downloaded from the website, you first need to go into "Manage app execution aliases". There you will find two python.exes checked as on. Check those off. Next, you need to replace the python environment variables that you just deleted. If you downloaded from python.org, after you install python (or during), you can click modify and on the second page there will be a button that you can press to add python environment variables. Click that and everything should work now.
