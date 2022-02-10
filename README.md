# Sort Command Implementation in C

## Workes for External Sorting of Files using Limited RAM specified in the program itself and also provides RAM used for a particular operation done.

### Working of Algorithm :

1. Reads file/files and segregates them into smaller files depending on the RAM size specified.
2. Used Quick Sort for sorting the files.
3. Merged all the small files to make a single sorted file.

### To run this project

`Clone the repository`

```
#Build the project
make s

#Generate random unsorted data
make t

#Run the program
Run ./a.out [options] filename
```

## Options available

```
-r Sorting the file in descending order

-o Saving the output in the file name specified

-d Sort based on dictionary order

-n Sort based on numerical values

-m Merges files specified as operands in a sorted order

-c check whether the given file is sorted

```
