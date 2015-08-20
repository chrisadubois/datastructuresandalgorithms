package Hw5;

//@Author: Christopher DuBois
import java.io.*;//import everything to do with file input and output from java

public class FindFile {
	ArrayList pathToFile = new ArrayList();// This is the arraylist that I created last hw
	private String fileName;// stores the file name to be searched
	private int count;// holds a count as the class searches for a particular file name
	private int maxFilesToFind;// holds the max number of files to find as defined in the specs
	public FindFile(int maxRepetitions) {// defines an object of this class by the repetitions it must search for the instance of a file
		if (maxRepetitions <= 0) {
			throw new IllegalArgumentException("Cannot enter 0 or negative values in the findFile object creation constructor call");
		}
		this.maxFilesToFind = maxRepetitions;
	}

	private void setFileName(String sFN) {// sets the file name to search for privately based on the search
		fileName = sFN;
	}

	public void directorySearch(String target, String dirName) {// target = what to be searched and dir name is the starting directory
		File directory = new File(dirName); // creates the directory string and makews it into a file
		this.setFileName(target);// sets the file name privately to target
		if (directory.isDirectory()) {// if the file directory is an instance of directory(from File io methods)
			searchInside(directory);// look inside the directory for the instance of the file name string
		} else {
			System.out.println(directory.getAbsoluteFile() + "error");// print out the path its taken so far and error if the next thing passed is not a directory
			throw new IllegalArgumentException("The path passed in as the starting directory is not a valid directory");// the initial directory that was passed did not work; illegal args
		}
	}

	private void searchInside(File checker) {// recursive method that searches inside of a directory to match the target fuile name with a file found inside of a directory
		if (checker.isDirectory()) {// as long as the File being passed in (which is indeed actually a directory) is a directory
			System.out.println("Now entering..." + checker.getAbsoluteFile());// show the programs ongoing paths as it looks for a file
			File[] check = checker.listFiles();// creates a file array of whats insiude the directory
			for (int i = 0; i < check.length; i++) {// for the length of the file array
				if (check[i].isDirectory()) {// if there are any directories inside of the directory being initially passed
					searchInside(check[i]);// recursively call and search
				} else {// this will continue checking until there is no more directories inside of the file being passed
					if (fileName.equals(check[i].getName())) {// checks to see if the file name string matches the file string name inside of the file array from the directory
						if (count < maxFilesToFind) {// continue adding the file paths as long as there havent been as many filed added in as the max number of files to search for
							pathToFile.insert(check[i].getAbsoluteFile()
									.toString());
							count++;// every time you add a path, increment count
							if (count == maxFilesToFind) {// once the maxNumber of files have been found, stop and exit gracefully
								System.out.println("Stopping file search at file # "+ maxFilesToFind);
								//System.out.println("The program encountered the max number of files to find in the search, it is possible there are more instances of this file name.");
								System.out.println(pathToFile.toString());
								// break;
								throw new RuntimeException("The program encountered the max number of files to find in the search, it is possible there are more instances of this file name.");
							}
						}
					}
				}

			}
		}
	}

	@Override
	public String toString() {// uses the arraylist to string that I created
		if (count < maxFilesToFind) {
			System.out.println("We found all the instances of the file. but please note that you requested to find " + maxFilesToFind + " files and we found " + count);
		}
		return pathToFile.toString();
	}

	public int getCount() {// simple getter
		return this.count;
	}

	public String[] getFiles() {// walking through two arrays and copying over the information to follow the specs.
		String[] retVal = new String[count];
		for (int i = 0; i < maxFilesToFind; i++) {
			String k = (String) pathToFile.get(i);// uses arraylist copiers.
			if (k.equals("No File Path")) {
				return retVal;
			} else {
				retVal[i] = k;
			}
		}
		return retVal;
	}
}
