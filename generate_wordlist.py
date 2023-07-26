# flake8: noqa
import mdformat  # pip install mdformat-myst
import pandas  # pip install pandas

template = """
# Dictionary

The lectures in this course is in norwegian, while the course material is in english. We strive to use the correct norwegian translation whenever this is available. The field of computer science and informatics is an international field and therefore, unfortunately, there aren't always a good norwegian words for all the words we use in the course.

While other fields in science have dedicated a vast amount of time into translating words between english and norwegian (see e.g <https://matematikkradet.no/ordliste/>) we were unable to find a good dictionary that covered the words used in this course.

Therefore we have put together a list of words here with norwegian (bokmål) and english translations of common words used in this course.

We would of course like to add more words as well as a new column with Norwegian (nynorsk) translations, but that takes time and unfortunately it is not the main priority.

```{note}
Contributions to this dictionary are more than welcomed. Please submit a pull request or send an email to [henriknf@simula.no](mailto:henriknf@simula.no?subject=Ordliste-IN1910)
```
"""

template_eng_to_nor = """
## English-Norwegian

| **English**            | **Norwegian**           |
| ---------------------- | ----------------------- |
{}
"""

template_nor_to_eng = """
## Norwegian-English

| **Norwegian**           | **English**            |
| ---------------------- | ----------------------- |
{}
"""

df = pandas.read_csv("wordlist.csv", header=0, dtype=str, encoding="utf-8")


eng_to_nor = ""
for _, row in df.sort_values("Engelsk").iterrows():
    eng_to_nor += f"| {row.Engelsk} | {row.Bokmål} |\n"

nor_to_eng = ""
for _, row in df.sort_values("Bokmål").iterrows():
    nor_to_eng += f"| {row.Bokmål} | {row.Engelsk} |\n"

text = (
    template
    + template_eng_to_nor.format(eng_to_nor)
    + template_nor_to_eng.format(nor_to_eng)
)

with open("book/docs/info/dictionary.md", "w", encoding="utf-8") as f:
    f.write(text)

# Make sure tables are formatted correctly
mdformat.file("book/docs/info/dictionary.md", extensions=["myst"])
