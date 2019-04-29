package objetRaid;

public class Inode {
	private char[] filename;
	private int size;
	private int nblock;
	private int firstByte;
	public static final int fileNameMaxSize = 32;
	
	Inode(char[] filename, int size, int nblock, int firstByte) {
		filename = new char[fileNameMaxSize];
		for (int i = 0; i < fileNameMaxSize; i++) {
			this.filename[i] = filename[i];
		}
		this.size = size;
		this.nblock = nblock;
		this.firstByte = firstByte;
	}

	public char[] getFilename() {
		return filename;
	}

	public int getSize() {
		return size;
	}

	public int getNblock() {
		return nblock;
	}

	public int getFirstByte() {
		return firstByte;
	}
	
}
