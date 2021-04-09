# A-star
## Introduction
This code repo implements 2D A-star path planning algorithm in C++.<br/>
The library has options to search in several different modes:<br/>
flag 1: search neighbors in 4 or 8 directions<br/>
flag 2: compute distance as 1 (manhattan) or 2 (euclidean)<br/>

A python file helps to illustrate the result.<br/>
(start cell: green, goal cell: red, path cell: blue)<br/>

## Usage
The system takes a binary 2D grid map with 0s and 1s representing traversable cell and obstales respectively.
All the inputs can be modified in the input.csv file easily.<br/>
To run the repo:<br/>
  1. Clone the repo
```
git clone https://github.com/LuoXin0826/Astar.git
```
  2. Modify the input.csv file
  3. Compile the code
```
mkdir build
cd build
cmake ..
make
./main
```
  4. Get visual result
```
python3 Draw_path.py
```
  5. Testing with different case is easy, just modify the input.csv file, you don't need to compile the code again. <br/>
## Example
For example, for world:<br/>
0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0<br/>
0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1<br/>
0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0<br/>
0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0<br/>
1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0<br/>
1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0<br/>
1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0<br/>
0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1<br/>
0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1<br/>
0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0<br/>
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0<br/>
And start point (0,0), goal point (10,10), searching 4 directions with Euclidien distance, the output result is: <br/>
<p align="center">
<img src="https://raw.githubusercontent.com/LuoXin0826/Astar/master/example_images/result_4.png" width="337" height="333">
</p>
searching 8 directions with Euclidien distance, the output result is: <br/>
<p align="center">
<img src="https://raw.githubusercontent.com/LuoXin0826/Astar/master/example_images/result_8.png" width="337" height="333">
</p>
