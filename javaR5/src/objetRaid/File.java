package objetRaid;

public class File {
	private int size;
	private char[] data;
	public File(int size, char[] data) {
		this.data = new char[size];
		for(int i = 0; i < size; i++) {
			this.data[i] = data[i];
		}
	}
	public int getSize() {
		return size;
	}
	public char[] getData() {
		return data;
	}
	
}
