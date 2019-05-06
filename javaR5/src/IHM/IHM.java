package IHM;
import objetRaid.Raid;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */





/**
 *
 * @author martinie
 */
public class IHM {

    static Fenetre fenetre = new Fenetre();
    static Raid raid5 = new Raid(5);
    
   /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Fenetre.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Fenetre.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Fenetre.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Fenetre.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                fenetre.setVisible(true);
            }
        });
    }
    
    public static void ouvrirFenetre(){
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                fenetre.setVisible(true);
                raid5.initRaid("../disk/raid5/");
                fenetre.ActualiserJlist();
                
                
                
            }
        });
    }
    
    public static void fermerFenetre(){
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                fenetre.setVisible(false);
                raid5.shutDownRaid();
                
            }
        });
    }
    
}
