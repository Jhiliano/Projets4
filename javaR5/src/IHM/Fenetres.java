/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package IHM;

import java.awt.Cursor;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import objetRaid.Raid;
/**
 *
 * @author ggfou
 */
public class Fenetres extends javax.swing.JFrame {

    /**
     * Creates new form Fenetres
     */
    public Fenetres() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        Erreur = new javax.swing.JOptionPane();
        PickFolder = new javax.swing.JFrame();
        FolderChooser = new javax.swing.JFileChooser();
        PickFile = new javax.swing.JFrame();
        FileChooser = new javax.swing.JFileChooser();
        DialogParametres = new javax.swing.JDialog();
        RetourParametres = new javax.swing.JButton();
        Defrag = new javax.swing.JButton();
        Reset = new javax.swing.JButton();
        jButton1 = new javax.swing.JButton();
        Informations = new javax.swing.JOptionPane();
        Entree = new javax.swing.JOptionPane();
        Pick = new javax.swing.JOptionPane();
        PanelPrincipal = new javax.swing.JPanel();
        jPanel2 = new javax.swing.JPanel();
        ListInode = new javax.swing.JComboBox<>();
        Parametres = new javax.swing.JButton();
        TauxFragmentation = new javax.swing.JLabel();
        Afficher = new javax.swing.JButton();
        NbFichiers = new javax.swing.JLabel();
        EspaceUtilise = new javax.swing.JLabel();
        EspaceRestant = new javax.swing.JLabel();
        jPanel1 = new javax.swing.JPanel();
        Create = new javax.swing.JButton();
        Delete = new javax.swing.JButton();
        Editer = new javax.swing.JButton();
        Exporter = new javax.swing.JButton();
        Importer = new javax.swing.JButton();
        jPanel3 = new javax.swing.JPanel();
        jScrollPane1 = new javax.swing.JScrollPane();
        FileArea = new javax.swing.JTextArea();

        Erreur.setBackground(new java.awt.Color(153, 153, 153));

        PickFolder.setTitle("Ouvrir un dossier raid 5");

        FolderChooser.setCurrentDirectory(new java.io.File("C:\\Program Files\\NetBeans 8.2"));
        FolderChooser.setDialogTitle("Ouvir dossier Raid 5");
        FolderChooser.setFileSelectionMode(javax.swing.JFileChooser.DIRECTORIES_ONLY);
        FolderChooser.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                FolderChooserActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout PickFolderLayout = new javax.swing.GroupLayout(PickFolder.getContentPane());
        PickFolder.getContentPane().setLayout(PickFolderLayout);
        PickFolderLayout.setHorizontalGroup(
            PickFolderLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 603, Short.MAX_VALUE)
            .addGroup(PickFolderLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(PickFolderLayout.createSequentialGroup()
                    .addGap(0, 0, Short.MAX_VALUE)
                    .addComponent(FolderChooser, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(0, 0, Short.MAX_VALUE)))
        );
        PickFolderLayout.setVerticalGroup(
            PickFolderLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 397, Short.MAX_VALUE)
            .addGroup(PickFolderLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(PickFolderLayout.createSequentialGroup()
                    .addGap(0, 0, Short.MAX_VALUE)
                    .addComponent(FolderChooser, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(0, 0, Short.MAX_VALUE)))
        );

        FileChooser.setCurrentDirectory(new java.io.File("C:\\Program Files\\NetBeans 8.2"));
        FileChooser.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                FileChooserActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout PickFileLayout = new javax.swing.GroupLayout(PickFile.getContentPane());
        PickFile.getContentPane().setLayout(PickFileLayout);
        PickFileLayout.setHorizontalGroup(
            PickFileLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(FileChooser, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, 621, Short.MAX_VALUE)
        );
        PickFileLayout.setVerticalGroup(
            PickFileLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(FileChooser, javax.swing.GroupLayout.DEFAULT_SIZE, 419, Short.MAX_VALUE)
        );

        DialogParametres.setTitle("Paramètres");
        DialogParametres.setMinimumSize(new java.awt.Dimension(265, 135));
        DialogParametres.setModal(true);
        DialogParametres.setResizable(false);

        RetourParametres.setText("Retour");
        RetourParametres.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        RetourParametres.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                RetourParametresActionPerformed(evt);
            }
        });

        Defrag.setIcon(new javax.swing.ImageIcon(getClass().getResource("/IHM/img/défragmenter.png"))); // NOI18N
        Defrag.setToolTipText("Défragmenter le disque");
        Defrag.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        Defrag.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                DefragActionPerformed(evt);
            }
        });

        Reset.setIcon(new javax.swing.ImageIcon(getClass().getResource("/IHM/img/supprimer.png"))); // NOI18N
        Reset.setToolTipText("Réinitialiser les disques");
        Reset.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        Reset.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ResetActionPerformed(evt);
            }
        });

        jButton1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/IHM/img/reparer.png"))); // NOI18N
        jButton1.setToolTipText("Reparer un disque");
        jButton1.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout DialogParametresLayout = new javax.swing.GroupLayout(DialogParametres.getContentPane());
        DialogParametres.getContentPane().setLayout(DialogParametresLayout);
        DialogParametresLayout.setHorizontalGroup(
            DialogParametresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(DialogParametresLayout.createSequentialGroup()
                .addComponent(Defrag)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 10, Short.MAX_VALUE)
                .addComponent(jButton1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 10, Short.MAX_VALUE)
                .addComponent(Reset))
            .addComponent(RetourParametres, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        DialogParametresLayout.linkSize(javax.swing.SwingConstants.HORIZONTAL, new java.awt.Component[] {Defrag, jButton1});

        DialogParametresLayout.setVerticalGroup(
            DialogParametresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, DialogParametresLayout.createSequentialGroup()
                .addGroup(DialogParametresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(Reset, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(Defrag, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jButton1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addGap(0, 10, Short.MAX_VALUE)
                .addComponent(RetourParametres))
        );

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Raid5");
        setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        setMinimumSize(new java.awt.Dimension(750, 547));
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                formWindowClosing(evt);
            }
        });

        jPanel2.setBorder(javax.swing.BorderFactory.createEtchedBorder());

        ListInode.addItemListener(new java.awt.event.ItemListener() {
            public void itemStateChanged(java.awt.event.ItemEvent evt) {
                ListInodeItemStateChanged(evt);
            }
        });
        ListInode.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ListInodeActionPerformed(evt);
            }
        });

        Parametres.setIcon(new javax.swing.ImageIcon(getClass().getResource("/IHM/img/paramètres.png"))); // NOI18N
        Parametres.setToolTipText("Paramètres");
        Parametres.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        Parametres.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ParametresActionPerformed(evt);
            }
        });

        TauxFragmentation.setText("Taux de fragmentation :");

        Afficher.setIcon(new javax.swing.ImageIcon(getClass().getResource("/IHM/img/visible.png"))); // NOI18N
        Afficher.setToolTipText("Afficher le fichier");
        Afficher.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Afficher.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                AfficherActionPerformed(evt);
            }
        });

        NbFichiers.setText("Nombre de fichiers :");

        EspaceUtilise.setText("Espace utilisé :");

        EspaceRestant.setText("Espace restant : ");

        javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addComponent(Parametres, javax.swing.GroupLayout.PREFERRED_SIZE, 33, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(27, 27, 27)
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(ListInode, 0, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(NbFichiers, javax.swing.GroupLayout.DEFAULT_SIZE, 374, Short.MAX_VALUE)
                    .addComponent(EspaceUtilise, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addGap(18, 18, 18)
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addComponent(Afficher)
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(TauxFragmentation, javax.swing.GroupLayout.PREFERRED_SIZE, 227, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(EspaceRestant, javax.swing.GroupLayout.PREFERRED_SIZE, 227, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(0, 37, Short.MAX_VALUE))))
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel2Layout.createSequentialGroup()
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(TauxFragmentation, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(NbFichiers, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(EspaceUtilise, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(EspaceRestant, javax.swing.GroupLayout.PREFERRED_SIZE, 22, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 10, Short.MAX_VALUE)
                        .addComponent(Afficher, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addComponent(Parametres)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(ListInode, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap())
        );

        Create.setIcon(new javax.swing.ImageIcon(getClass().getResource("/IHM/img/ajouter-le-fichier.png"))); // NOI18N
        Create.setToolTipText("Ajouter un fichier");
        Create.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                CreateActionPerformed(evt);
            }
        });

        Delete.setIcon(new javax.swing.ImageIcon(getClass().getResource("/IHM/img/supprimer-le-fichier.png"))); // NOI18N
        Delete.setToolTipText("Supprimer un fichier");
        Delete.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Delete.setEnabled(false);
        Delete.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                DeleteActionPerformed(evt);
            }
        });

        Editer.setIcon(new javax.swing.ImageIcon(getClass().getResource("/IHM/img/editer-le-fichier.png"))); // NOI18N
        Editer.setToolTipText("Editer le fichier");
        Editer.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Editer.setEnabled(false);
        Editer.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                EditerActionPerformed(evt);
            }
        });

        Exporter.setIcon(new javax.swing.ImageIcon(getClass().getResource("/IHM/img/exporter.png"))); // NOI18N
        Exporter.setToolTipText("Exporter un fichier");
        Exporter.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Exporter.setEnabled(false);
        Exporter.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ExporterActionPerformed(evt);
            }
        });

        Importer.setIcon(new javax.swing.ImageIcon(getClass().getResource("/IHM/img/importer.png"))); // NOI18N
        Importer.setToolTipText("Importer un fichier");
        Importer.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ImporterActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(Create, javax.swing.GroupLayout.DEFAULT_SIZE, 120, Short.MAX_VALUE)
            .addComponent(Delete, javax.swing.GroupLayout.DEFAULT_SIZE, 120, Short.MAX_VALUE)
            .addComponent(Editer, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, 120, Short.MAX_VALUE)
            .addComponent(Exporter, javax.swing.GroupLayout.DEFAULT_SIZE, 120, Short.MAX_VALUE)
            .addComponent(Importer, javax.swing.GroupLayout.DEFAULT_SIZE, 120, Short.MAX_VALUE)
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(0, 0, 0)
                .addComponent(Editer, javax.swing.GroupLayout.PREFERRED_SIZE, 82, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, 0)
                .addComponent(Create, javax.swing.GroupLayout.PREFERRED_SIZE, 82, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, 0)
                .addComponent(Delete, javax.swing.GroupLayout.PREFERRED_SIZE, 82, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, 0)
                .addComponent(Exporter, javax.swing.GroupLayout.PREFERRED_SIZE, 82, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, 0)
                .addComponent(Importer, javax.swing.GroupLayout.PREFERRED_SIZE, 82, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        FileArea.setColumns(20);
        FileArea.setRows(5);
        jScrollPane1.setViewportView(FileArea);

        javax.swing.GroupLayout jPanel3Layout = new javax.swing.GroupLayout(jPanel3);
        jPanel3.setLayout(jPanel3Layout);
        jPanel3Layout.setHorizontalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jScrollPane1)
        );
        jPanel3Layout.setVerticalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 450, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout PanelPrincipalLayout = new javax.swing.GroupLayout(PanelPrincipal);
        PanelPrincipal.setLayout(PanelPrincipalLayout);
        PanelPrincipalLayout.setHorizontalGroup(
            PanelPrincipalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(PanelPrincipalLayout.createSequentialGroup()
                .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, 0)
                .addComponent(jPanel3, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addComponent(jPanel2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        PanelPrincipalLayout.setVerticalGroup(
            PanelPrincipalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(PanelPrincipalLayout.createSequentialGroup()
                .addComponent(jPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, 0)
                .addGroup(PanelPrincipalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jPanel3, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(PanelPrincipal, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(PanelPrincipal, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        pack();
        setLocationRelativeTo(null);
    }// </editor-fold>//GEN-END:initComponents

    private void AfficherActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_AfficherActionPerformed
        String edit;
        String s = ListInode.getSelectedItem().toString();
        if(s != null) {
            edit = IHM.raid5.afficherFichier(s);
            if(edit.equals("")) {
                JOptionPane.showMessageDialog(Erreur,"Fichier innexistant","Erreur",JOptionPane.ERROR_MESSAGE);
            }
            else {
                FileArea.setText(edit);
                Editer.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
                Editer.setEnabled(true);
            }
        }
        else {
            JOptionPane.showMessageDialog(Erreur,"Aucunne valeur seletionné","Erreur",JOptionPane.ERROR_MESSAGE);
        }
        actualiserInfos();
    }//GEN-LAST:event_AfficherActionPerformed

    private void ListInodeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ListInodeActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_ListInodeActionPerformed

    private void ParametresActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ParametresActionPerformed
        DialogParametres.setLocationRelativeTo(this);
        DialogParametres.setVisible(true);
    }//GEN-LAST:event_ParametresActionPerformed

    private void FolderChooserActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_FolderChooserActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_FolderChooserActionPerformed

    private void FileChooserActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_FileChooserActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_FileChooserActionPerformed

    private void RetourParametresActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_RetourParametresActionPerformed
        DialogParametres.setVisible(false);
    }//GEN-LAST:event_RetourParametresActionPerformed

    private void DefragActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_DefragActionPerformed
        if(IHM.raid5.defrag() != 0) {
            JOptionPane.showMessageDialog(Erreur,"Erreur dans la defragmentation","Erreur",JOptionPane.ERROR_MESSAGE);
        }
        else {
            JOptionPane.showMessageDialog(Informations,"Defragmentation effectuée","Information",JOptionPane.INFORMATION_MESSAGE);
        }
        actualiserInfos();
    }//GEN-LAST:event_DefragActionPerformed

    private void ResetActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ResetActionPerformed
        int size = 0;
        String input;
        do {
            input = JOptionPane.showInputDialog(Entree,"Entrez la taille par disques","Creation disques",JOptionPane.INFORMATION_MESSAGE); 
            if (input != null) {
                try {
                    size = Integer.parseInt(input);
                    if (size < 51200) {
                        JOptionPane.showMessageDialog(Erreur,"Cela doit etre une valeur superieur ou egal a 52000","Erreur",JOptionPane.ERROR_MESSAGE);
                    }
                }
                catch (NumberFormatException e) {
                         JOptionPane.showMessageDialog(Erreur,"Cela doit etre une valeur en int","Erreur",JOptionPane.ERROR_MESSAGE);
                }
            }
        } while((size < 51200 || size%4 != 0) && input != null);
        if(input != null) {
            if(IHM.raid5.reinitialiser(size) != 0) {
                JOptionPane.showMessageDialog(Erreur," Erreur dans la réinitialisation des disques","Erreur",JOptionPane.ERROR_MESSAGE);
            } else {
                JOptionPane.showMessageDialog(Informations,"Disques réinitialisés avec une taille de " + size + " par disques" ,"Information",JOptionPane.INFORMATION_MESSAGE);
            }
        }
        actualiserInfos();
    }//GEN-LAST:event_ResetActionPerformed

    private void ImporterActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ImporterActionPerformed
        String s = this.choixfichier(FileChooser);
        if(IHM.raid5.loadFileToHost(s) != 0) {
            JOptionPane.showMessageDialog(Erreur,"Fichier incorrect","Erreur",JOptionPane.ERROR_MESSAGE);
        }
        actualiserInfos();
    }//GEN-LAST:event_ImporterActionPerformed

    private void ExporterActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ExporterActionPerformed
        if (ListInode.getSelectedItem() == null) {
            JOptionPane.showMessageDialog(Erreur,"Aucun fichier dans le raid","Erreur",JOptionPane.ERROR_MESSAGE);
        } else {
            String nomFichier = ListInode.getSelectedItem().toString();
            if(nomFichier == null) {
                JOptionPane.showMessageDialog(Erreur,"Veuillez selectionner un fichier","Erreur",JOptionPane.ERROR_MESSAGE);
            } else {
                if(IHM.raid5.storeFileToHost(nomFichier) != 0) {
                    JOptionPane.showMessageDialog(Erreur,"fichier incorrect","Erreur",JOptionPane.ERROR_MESSAGE);
                }
                actualiserInfos();
            }
            
        }
    }//GEN-LAST:event_ExporterActionPerformed

    private void EditerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_EditerActionPerformed
        String edit = FileArea.getText();
        if(edit == null) {
            JOptionPane.showMessageDialog(Erreur,"Il y a rien a enregistrer","Erreur",JOptionPane.ERROR_MESSAGE);
        }
        else {
            if(IHM.raid5.editerFichier(edit) != 0) {
                JOptionPane.showMessageDialog(Erreur,"Il y a rien a enregistrer","Erreur",JOptionPane.ERROR_MESSAGE);
            }
        }
        actualiserInfos();
    }//GEN-LAST:event_EditerActionPerformed

    private void DeleteActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_DeleteActionPerformed
        if(ListInode.getSelectedItem() == null) {
            JOptionPane.showMessageDialog(Erreur,"Aucun fichier dans le raid","Error",JOptionPane.ERROR_MESSAGE);
        } else {
            if(ListInode.getSelectedItem().toString() == null) {
                JOptionPane.showMessageDialog(Erreur,"Veuillez selectionner un fichier","Erreur",JOptionPane.ERROR_MESSAGE);
            } else {
                if(IHM.raid5.deleteFile(ListInode.getSelectedItem().toString()) != 0) {
                    JOptionPane.showMessageDialog(Erreur,"Fichier Incorrect","Erreur",JOptionPane.ERROR_MESSAGE);
                }
                actualiserInfos();
            }
        }
        
    }//GEN-LAST:event_DeleteActionPerformed

    private void CreateActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_CreateActionPerformed
        if(IHM.raid5.ajouterFichier(JOptionPane.showInputDialog(Erreur,"Ecrivez le nom du fichier","Creation fichier",JOptionPane.INFORMATION_MESSAGE)) != 0) {
            JOptionPane.showMessageDialog(Erreur,"Erreur de création","Erreur",JOptionPane.ERROR_MESSAGE);
        }
        actualiserInfos();
    }//GEN-LAST:event_CreateActionPerformed

    private void formWindowClosing(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowClosing
        IHM.raid5.shutDownRaid();
    }//GEN-LAST:event_formWindowClosing

    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed
        int disque;
        String nomDisqueAReparer;
        String[] nomDisque = new String[IHM.raid5.getNbDisk()];
        for(int d = 0; d <nomDisque.length; d++) {
            nomDisque[d] = Integer.toString(d + 1);
        }
        nomDisqueAReparer = (String) JOptionPane.showInputDialog(null, "veuillez choisir le disque à reparer", "Reparation", JOptionPane.QUESTION_MESSAGE, null, nomDisque, nomDisque[0]);
        if(nomDisqueAReparer != null) {
            disque = Integer.parseInt(nomDisqueAReparer);
            if(IHM.raid5.reparer(disque-1) == 0) {
                JOptionPane.showMessageDialog(Informations,"Disque " + disque + " réparé avec succès !" ,"Information",JOptionPane.INFORMATION_MESSAGE);
            }
            else {
                JOptionPane.showMessageDialog(Erreur,"Erreur de reparation","Erreur",JOptionPane.ERROR_MESSAGE);
            }
        }

    }//GEN-LAST:event_jButton1ActionPerformed

    private void ListInodeItemStateChanged(java.awt.event.ItemEvent evt) {//GEN-FIRST:event_ListInodeItemStateChanged
        if(ListInode.getSelectedItem() == null) {
            Afficher.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
            Exporter.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
            Delete.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
            Afficher.setEnabled(false);
            Exporter.setEnabled(false);
            Delete.setEnabled(false);
        } else {
            Afficher.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
            Exporter.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
            Delete.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
            Afficher.setEnabled(true);
            Exporter.setEnabled(true);
            Delete.setEnabled(true);
        }
    }//GEN-LAST:event_ListInodeItemStateChanged

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
            java.util.logging.Logger.getLogger(Fenetres.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Fenetres.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Fenetres.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Fenetres.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Fenetres().setVisible(true);
            }
        });
    }
    
        void actualiserInfos() {
        int selectedItem = ListInode.getSelectedIndex();
        ListInode.removeAllItems();
            for (int i = 0; i<Raid.inodeTableSize; i++) {
		if(IHM.raid5.inodeFiled(i)) {
                    ListInode.addItem(IHM.raid5.getInodeName(i));
		}
            }
        EspaceRestant.setText("Espace restant : " + Long.toString(IHM.raid5.getSizeLeft()));
        EspaceUtilise.setText("Espace utilisé : " + Long.toString(IHM.raid5.getSizeUsed()));
        NbFichiers.setText("Nombre de fichiers : " + Integer.toString(IHM.raid5.getNumberOfFiles()));
        TauxFragmentation.setText("Taux de fragmentation : " + Integer.toString(IHM.raid5.getSizeFragmentation()) + "%");
        if(selectedItem < ListInode.getItemCount()) {
            ListInode.setSelectedIndex(selectedItem);
        }
        if(IHM.raid5.getNumberOfFiles() < 10) {
            Create.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
            Importer.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
            Create.setEnabled(true);
            Importer.setEnabled(true);
        } else {
            Create.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
            Importer.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
            Create.setEnabled(false);
            Importer.setEnabled(false);
        }
 }
    
    String choixfichier(JFileChooser jfc) {
        jfc.updateUI();
    	int retour = jfc.showOpenDialog(this);
        if (retour==JFileChooser.APPROVE_OPTION) {
                try {
                    return jfc.getSelectedFile().getCanonicalPath();
                } catch (IOException ex) {
                    Logger.getLogger(Fenetres.class.getName()).log(Level.SEVERE, null, ex);
                }
        }
        return "";
        
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton Afficher;
    private javax.swing.JButton Create;
    private javax.swing.JButton Defrag;
    private javax.swing.JButton Delete;
    private javax.swing.JDialog DialogParametres;
    private javax.swing.JButton Editer;
    private javax.swing.JOptionPane Entree;
    javax.swing.JOptionPane Erreur;
    private javax.swing.JLabel EspaceRestant;
    private javax.swing.JLabel EspaceUtilise;
    private javax.swing.JButton Exporter;
    private javax.swing.JTextArea FileArea;
    private javax.swing.JFileChooser FileChooser;
    javax.swing.JFileChooser FolderChooser;
    private javax.swing.JButton Importer;
    private javax.swing.JOptionPane Informations;
    private javax.swing.JComboBox<String> ListInode;
    private javax.swing.JLabel NbFichiers;
    private javax.swing.JPanel PanelPrincipal;
    private javax.swing.JButton Parametres;
    private javax.swing.JOptionPane Pick;
    private javax.swing.JFrame PickFile;
    private javax.swing.JFrame PickFolder;
    private javax.swing.JButton Reset;
    private javax.swing.JButton RetourParametres;
    private javax.swing.JLabel TauxFragmentation;
    private javax.swing.JButton jButton1;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JScrollPane jScrollPane1;
    // End of variables declaration//GEN-END:variables
}
