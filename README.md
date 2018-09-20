# OMH

## Introduction

Hash table is a classic data structure, and is widely used in various fields of computer science. For many applications, its worst-case query performance is critical. Among prior art, only perfect hash tables can achieve one memory access per query in the worst case. However, they do not support fast incremental updates, and suffer from the possibility of update failures. In this paper, we propose the One-Memory Hash table, which achieves one memory access per query in the worst case, while supporting fast incremental updates and guaranteeing no update failure.  The key technique is to build exclusive fingerprints. We implement the One-Memory Hash table on GPU/CPU, and FPGA platforms, and conduct head-to-head comparisons with 9 prior hash schemes on 3 real-world and 1 synthetic datasets. Experimental results show that the One-Memory Hash table significantly outperforms all prior work.

## About the source codes and datasets.

In the document "all_sketch", there are several files, representing the corresponding skethes, which are mentioned in the paper.

In the document "experiments_code", there is one file named "docid500w.dat", which is a sample dataset, and other subdocuments. The name of the subdocument represents the application of the codes in it.

We use in total 4 datasets in our experiments, including 3 real-world datasets and 1 synthetic dataset.

Taxi: This dataset includes over 1.7 million records of the trajectories performed by 442 taxis running in the city of Porto, in Portugal. Each record includes a trip ID, a timestamp, a taxi ID as well as other fields. We use the trip ID and taxi ID as our $<key,value>$ pairs.

Post: This dataset includes over 5 million records of the training instances. Each record includes six fields: ID1, ID2, name, date of birth, postcode and matching status. We joint ID1 and ID2 in one record together as our key and use the matching status as our value.

DocWords:  This dataset includes multiple text collections in the form of bag-of-words. It contains nearly 70 million items in total. Each item contains several fields. We combine the DocID and WordID fields as our $<key,value>$ pairs. Among the 70 million items, we sample 10 million to form the experimental dataset.

Synthetic: This dataset is generated using the C++ STL Mersenne Twister random integer generator. The generated integers are unsigned 32-bit long, and follow a pseudo-random uniform distribution. 5 million integers are generated in total.
	
## How to run

Suppose you've already cloned the repository and start from the Codes directory.

In the document "experiments_code", you need to move the dataset to some subdocument and run "one_mem_hash.cpp", the results which corresponds to the figure in the paper will be shown on the screen.

If you want to change some parameters, please read the code.

## About code in GPU

There is a file called add2.cu in the GPU document. You can run this code with the following cimpilation options.

nvcc -DDATA_PATH=/*path*/ -DBATCH_SIZE=/*batch size*/ add2.cu

## Output format

We set some variables for every code. They will give you any information you want.