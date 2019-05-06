package objetRaid;

public class Tests {
	public static void main(String args[])  {
		Raid raid5 = new Raid(5);
		raid5.initRaid("../disk/raid5/");
		System.out.println(raid5.storeFileToHost("../tests/in/image1.png"));
		System.out.println(raid5.storeFileToHost("../tests/in/image2.png"));
		System.out.println(raid5.loadFileToHost("../tests/in/image1.png"));
		System.out.println(raid5.loadFileToHost("../tests/in/image2.png"));
		raid5.shutDownRaid();
	}
}
