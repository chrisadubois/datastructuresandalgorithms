package Hw5;

public class fileDrive {
	
	public static void main (String[] args) {
		FindFile a = new FindFile(4);//tested with 1 exception gets thrown (3 files in my directory of this file name instance
		
		a.directorySearch("testFile.txt", "C:\\TestFolder");
		System.out.println(a.toString());
		String [] six = a.getFiles();
		for (int i = 0; i < six.length; i++) {
			System.out.print(six[i] + ",");
		}
		//a.directorySearch("testFile.txt", "C://ChristopherDuBoisOAPositionScheduling");//tested to pass in a file, which is not a directory.
	}
}
