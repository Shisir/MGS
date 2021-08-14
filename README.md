# MGS
Welcome to the code of the proposed method Mutual information Gene Selection (MGS).
There are two folders inside the MGS folder such as
  a. matlab
     Candidate features are selected by executing the main.m file.
     Here, a mat file is saved which will be used as input to the python file (located in python folder) for selecting features and measuring the performance.
     The mat file contains the indices of the selected candidate feature, discritized labels and MGS values.
  b. python
     Final features are selected using geneSelection.ipynb file that uses the mat file generated from matlab code (located on matlab folder).
     Then, the performance metrics are calculated of the selected features using validation.ipynb file.
