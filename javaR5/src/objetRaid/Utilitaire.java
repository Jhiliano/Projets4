package objetRaid;

import java.nio.ByteBuffer;

public class Utilitaire {
	public static int byte_to_int(byte[] octet, int pos) {
	    ByteBuffer byteBuffer = ByteBuffer.wrap(octet, pos, 4);
	    return byteBuffer.getInt();
	}
	
	public static void int_to_byte(byte[] octet, int nombre, int pos) {
		for(int i = 0; i < 4; i += 1) {
			octet[pos+i] = (byte) ((nombre >> (8*(3-i))) & 0xff); // on prend d'abord les 8*sizeof(uint) bits a gauche et ensuite les suivant ect..
		}
	}
	public static int sizeWithParity(int size, Raid raid) {
		return Stripe.computeNStripe(Block.computeNBlock(size), raid.getNbDisk())*Block.size;
	}
}
