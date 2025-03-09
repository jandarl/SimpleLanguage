Simple Programming Language:

	- A simple programming language that aims to be easily understandable with lesser reserved words or procedures to learn
	- This programming language will aim to be as memory safe as possible although currently it will only be using stack memory
	- Type safety should be prioritized in the compiler level
	- For this phase, this will not be full OOP as currently there is no support for many of the OOP features such as Inheritance, hopefully this can also be added into the future
	- The file extension will be (.spl) 
	- The main entry point file will be name main.spl
	- Currently, there is no equivalent to a library file (.lib, .dll) but hopefully it can be added in the future
	- Current compiler will be created using C++

 1) Declaring a variable:
    ```
	let --> declare a mutable variable
			let i = 3;
			let f = 3.0;
			let c = 'C';
			let s = "String";
			let s2 = s;

	pb --> allow the variable to be accessible to outside of the file or the Proto.
			let pb i = 3;
			const pb f = 3.0;
			
	const --> declare an immutable variable
			const i = 3;
			const f = 3.0;
			const c = 'C';
			const s = "String";
			const s2 = s;
    ```
2) Functions:
   ```
	let ---> if a function will return something
	nothing if no return value.
	
	let i = (a, b){ return a + b; }
	let s = () { return "hello"; }
	v = () { print("world"); }
	p = (a, b) { print(a + b); }

	let pb i = (a,b) { return a + b }	<--- Public function that can be accessed outside the file or Proto.
   ```
4) Comments:
   ```
	/*This is a comment*/
	/*
	  This is a multi-line
	  comment
	*/
   ```
	
3) Control Flow:
   ```
	Conditionals:
		if, elif, else
			if conditional { do something }
			elif conditional { do something }
			else { do something }
			
		if-case --> ( switch-case equivalent )
			if input {
				a: {}
				b: {}
				c: {}
				else: {}
			}
   ```
   ```
	Looping:
		loop expression / condition {}
		while loop equivalent:
			loop i < 9 { do something }
		
		for/foreach loop equivalent:
			loop x in span(0,10) { do something }     <--- for( int x(0); x < 10; x+=1) in c++
			loop x in span(0,10,2) { do something }   <--- for( int x(0); x < 10; x+=2) in c++

			loop x in span(10,0) { do something }     <---- for( int x(10-1); x >= 0; x-=1) in c++
			loop x in span(10,0,2) { do something }   <---- for( int x(10-1); x >= 0; x-=2) in c++

			loop x in span(arr) {do something}        <---- for(int x(arr.beg()); x < arr.size(); x+=1) in c++
			loop x in span(arr, 2) {do something}     <---- for(int x(arr.beg()); x < arr.size(); x+=2) in c++ 
			loop x in span(arr, 5, 2) {do something}  <---- for(int x(arr.beg()); x < 5; x+=2) in c++
			loop x in span(3, arr, 2) {do something}  <---- for(int x(3); x < arr.size(); x+=2) in c++

			loop x in span(-arr) {do something}       	  <---- for(int x(arr.size() -1); x >= 0; x-=1) in c++
			loop x in span(-arr, 2) {do something}  	  <---- for(int x(arr.size() -1); x >= 0; x-=2) in c++ 
			loop x in span(-arr, 5, 2) {do something}     <---- for(int x(arr.size() -1); x >= 5; x-=2) in c++ 
			loop x in span(-3, arr, 2) {do something}     <---- for(int x(arr.size() -3); x >= 0; x-=2) in c++ 

			loop x,y in span(arr) {do something}      		<---- for(int x(arr.beg()); x < arr.size(); x+=1) in c++ with y as the arr[x]			
			loop x,y in span(arr, 2) {do something}   		<---- for(int x(arr.beg()); x < arr.size(); x+=2) in c++ with y as the arr[x]
			loop x,y in span(arr, 5, 2) {do something} 	    <---- for(int x(arr.beg()); x < 5; x+=2) in c++ with y as the arr[x]
			loop x,y in span(3, arr, 2) {do something}		<---- for(int x(3); x < arr.size(); x+=2) in c++ with y as the arr[x]
	
			loop x,y in span(-arr) {do something}     		<---- for(int x(arr.size() -1); x >= 0; x-=1) in c++ with y as arr[x]
			loop x,y in span(-arr, 2) {do something}  		<---- for(int x(arr.size() -1); x >= 0; x-=2) in c++ with y as arr[x]
			loop x,y in span(-arr, 5, 2) {do something}     <---- for(int x(arr.size() -1); x >= 5; x-=2) in c++ with y as arr[x]
			loop x,y in span(-3, arr, 2) {do something}     <---- for(int x(arr.size() -3); x >= 0; x-=2) in c++ with y as arr[x]
			
			loop x in span(map) {do something}         <---- iteration of a map with x as key
			loop x,y in span(map) {do something}       <---- iteration of a map with x as key and y as value

			loop x in span(set) {do something}		   <---- iteration of a set with x as the keyval
   ```
   ```		
	Statements:
		Label:
			:label_name
				:myLabel
				
		Continue, Return, Break:
			continue, return, break
		
		goto:
			goto label_name;
				goto myLabel;
   ```
	
5) User defined data types:
   ```
	Structs:
		let struct_name = s!{ 
			variable1,
			variable2,
			variable3
		}
		
		let struct_name = s!{ 
			variable1 = 'c',
			variable2 = 3,
			variable = "string"
		}

	Instantiation and Usage:
		struct_name mystruct;
		let data = mystruct.variable1;
   ```
   ```
	Enums:
		let enum_name = e!{
			enum1, 
			enum2, 
			enum3
		}
		
		let enum_name = e!{
			enum1 = 0, 
			enum2 = 1, 
			enum3 = 2
		}
   ```
   ```	
	Unions:
		let union_name = u!{
			variable1,
			variable2,
			variable3
		}
   ```
   ```	
	Proto:
		let proto_name = p!{
			let variable1;		<----- private
			let pb variable2;   <----- public
			
			let pb func1 = (a) { return a + me.variable1; }
			pb func2 = (b) { print(b + me.variable2); }
			
			let internal_func = () { return me.variable1 + me.variable2; }
		}
   ```

7) Simple Data Structures:
   ```
	Note: Data Structures declared as const will not be changed
		  even if the user tries to use the fucntions that modify
		  the data structure
	
	Array:
		let array = a[1,2,3,4,5,...];
		const array = a[1,2,3,4,5,...];
		let array = a[];

		functions:
		let len = () 				- size of the array
		push = (data) 				- push data at the back of the array
		stack = (data)				- stack a data at the front of the array
		insert = (index, data)			- insert the data at the indicated index
		let front = ()				- get the data at the front of the array
		let back = ()				- get the data at the back of the array
		let pop = (front)			- delete a value from the array and return the value. front = true if pop front, false if pop back
		remove = (index)			- remove the data of the indicated index from the array, resize the array afterwards
		clear = ()				- delete all the data in the array
		[index] = (data)			- modifies a data at the indicated index
		let [index] = ()			- get the data at the indicated index
		fill = (size, data)			- resize the array to equivalent of the size and fill it with the given data
   ```
   ```
	Set:
		let set = s[keyval,keyval,keyval,...];
		const set = s[keyval,keyval,keyval,...];
		let set = s[];

		let len = () 				- size of the set
		let test = (data)			- return true if data exists and false if not
		insert = (data)				- insert the data to the set
		remove = (data)				- remove data from the set
		clear = ()				- delete all the data in the set
   ```
   ```
	Map:
		let map = m[key1,value1;key2,value2;...];
		const map = m[key1,value1;key2,value2;...];
		let map = m[];

		let len = () 				- size of the map
		let test = (key)			- return true if key exists and false if not
		let [key] = ()				- return the data of the indicated key, will cause a violation if key is not present, use test first
		[key] = (data)				- insert a key with its data on the map
		remove = (key)				- removes the key and its data from the map
		clear = ()				- delete all the data in the map
   ```
   ```
	Tuple:
		let tuple = t[data1,data2,data3];
		const tuple = t[data1,data2,data3];
		
		function:
		let [index] = () 			- get the data at the indicated index
		[index] = (data)			- modify the data at the indicated index
   ```
   ```
	Two-dimensional Data Structures:
		Note: This applies to all simple data structures, array was just given as example

		let array_of_array = a[a[1,2,3],[1,2,3],[1,2,3]];
		let array_of_array = a[a[]];

		let array_of_map = a[m[key,val;key,val],[key,val;key,val]];
		let array_of_map = a[m[]];

		let array_of_set = a[s[keyval,keyval],[keyval,keyval]];
		let array_of_set = a[s[]];

		let array_of_tuple = a[t[data,data],[data,data]];
		let array_of_tuple = a[t[]];
   ```
		
9) Special Commands / Functions:
    ```
	Declarations: 
		use file_name				- use must be declared at the start of the file before any variable, data type, data structure or function has been defined.

	Functions:
		let main = () {do something then return exit value} 	  - the main entry point function for the program without commandline args
		let main = (args) {do something then return exit value}   - the main entry point function for the program with commandline args as an array of strings delimited by space
    ```
    
