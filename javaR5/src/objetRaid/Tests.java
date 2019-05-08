package objetRaid;
/**
 * Classe test du raid
 * @author Guillaume Fourcroy
 * @version 1.0
 */
public class Tests {
	public static void main(String args[])  {
		Raid raid5 = new Raid(5);
		raid5.initRaid("../disk/raid5/");
		//System.out.println(raid5.storeFileToHost("../tests/in/image1.png"));
		//System.out.println(raid5.loadFileToHost("../tests/in/image2.png"));
		//System.out.println(raid5.loadFileToHost("../tests/in/image1.png"));
		//System.out.println(raid5.loadFileToHost("../tests/in/text1.txt"));
		//System.out.println(raid5.afficherFichier("../tests/in/text1.txt"));
		//System.out.println(raid5.deleteFile("../tests/in/image2.png"));
		//System.out.println(raid5.deleteFile("../tests/in/text1.txt"));
		//System.out.println(raid5.deleteFile("../tests/in/image1.png"));
		//System.out.println(raid5.reparer(1));
		//raid5.reinitialiser(50*1024);
		for (int i = 0; i<Raid.inodeTableSize; i++) {
			if(raid5.getInodes()[i].getFirstByte() != 0) {
				System.out.println(i);
				System.out.println(raid5.getInodes()[i].getFilename());
				System.out.println(raid5.getInodes()[i].getFirstByte());
				System.out.println(raid5.getInodes()[i].getNblock());
				System.out.println(raid5.getInodes()[i].getSize());
			}
		}
		System.out.println(raid5.getSuperblock().getFirstFreeByte());
		//System.out.println(raid5.defrag());
		//System.out.println(raid5.afficherFichier("../tests/in/text1.txt"));
		//System.out.println(raid5.editerFichier("miam121234"));
		//System.out.println(raid5.afficherFichier("../tests/in/text1.txt"));
		System.out.println(raid5.getDisk()[0].length());
		raid5.shutDownRaid();
	}
}
