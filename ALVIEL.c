#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************/

typedef struct
{
    gchar temps[30];
    gchar details[100];
    int numero;
    int prix_total;
    gchar chef[20];
    gchar client[20];
    gchar rayon[20];
    gchar etat[15];

}   COMMANDE;

typedef struct
{
    gchar nom[20];
    gchar categorie[20];
    gchar details[30];
    gchar rayon[20];
    gchar etat[15];

}   VENDEUR;

typedef struct
{
    int prix;
    gchar categorie[10];
    gchar nom[20];
    gchar etat[15];
    gchar date[20];

}   ARTICLE;

typedef struct
{
    int depense;
    gchar categorie[20];
    gchar nom[20];
    gchar genre[7];

}   CLIENT;

typedef struct
{
    int capacite;
    gchar nom[20];
    gchar etat[50];
    gchar debut[30];
    gchar fin[30];
}   Fournisseur;

/******************************************************************************/

GtkBuilder *builder;
GtkWindow  *PageConnexion;
GtkWindow  *Principale;
GtkWidget  *AddArticle;
GtkWidget  *AddSalarie;
GtkWidget  *AddFournisseur;
GtkWidget  *AddVendeurRayon;
GtkWidget  *Commande;
GtkWidget  *ModifArticle;
GtkWidget  *ModifSalarie;
GtkWidget  *ModifFournisseur;

/******************************************************************************/

void on_button1_clicked ()    // Restaurant Info
{
    GtkEntry *entry1, *entry2;
    gtk_widget_hide (GTK_WIDGET(PageConnexion));

    entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "entry1"));
    entry2 = GTK_ENTRY(gtk_builder_get_object(builder, "entry2"));

    const gchar *entry1Text = gtk_entry_get_text (entry1);
    const gchar *entry2Text = gtk_entry_get_text (entry2);

    FILE *AlvielInfo;
    AlvielInfo = fopen ("db/AlvielInfo.txt", "w");
    fprintf(AlvielInfo, "%s\n%s\n", entry1Text, entry2Text);
    fclose (AlvielInfo);

    gtk_widget_show (GTK_WIDGET(Principale));
    gtk_window_set_title (Principale, entry1Text);


}

void on_button2_clicked ()    // Afficher Ajouter Article
{
    gtk_widget_show(AddArticle);
}

void on_button3_clicked ()    // Ajouter un nouvel article
{

    GtkComboBoxText  *categoriecombobox, *etatcombo;
    GtkLabel         *categorylabel, *etatlabel;
    categoriecombobox =  GTK_COMBO_BOX_TEXT (gtk_builder_get_object(builder, "comboboxtext1"));
    etatcombo   =  GTK_COMBO_BOX_TEXT (gtk_builder_get_object(builder, "comboboxtext2"));
    categorylabel =  GTK_LABEL (gtk_builder_get_object(builder, "label18"));
    etatlabel   =  GTK_LABEL (gtk_builder_get_object(builder, "label21"));

    GtkEntry  *nomarticle = GTK_ENTRY(gtk_builder_get_object(builder, "entry3"));
    GtkLabel  *namelabel =  GTK_LABEL (gtk_builder_get_object(builder, "label19"));

    GtkSpinButton *buttonprix = GTK_SPIN_BUTTON (gtk_builder_get_object(builder, "spinbutton2"));
    GtkLabel  *pricelabel =  GTK_LABEL (gtk_builder_get_object(builder, "label20"));

    gchar *categorie = NULL;
    categorie = gtk_combo_box_text_get_active_text (categoriecombobox);
    gchar *etat = NULL;
    etat = gtk_combo_box_text_get_active_text (etatcombo);

    const gchar *nom = gtk_entry_get_text (nomarticle);
    int prix = gtk_spin_button_get_value_as_int (buttonprix);

    gboolean categoriebool = TRUE, etatbool = TRUE, nombool = TRUE, prixbool = TRUE;

    if (categorie == NULL)
    {
        gtk_label_set_text (categorylabel, "Erreur");
        categoriebool = FALSE;
    }
    else
        gtk_label_set_text (categorylabel, " ");

    if (etat == NULL)
    {
        gtk_label_set_text (etatlabel, "Erreur");
        etatbool = FALSE;
    }
    else
        gtk_label_set_text (etatlabel, " ");

    if (strcmp(nom, "Nom") == 0)
    {
        gtk_label_set_text (namelabel, "Erreur");
        nombool = FALSE;
    }
    else
        gtk_label_set_text (namelabel, " ");

    if (prix == 0)
    {
        gtk_label_set_text (pricelabel, "Erreur");
        prixbool = FALSE;
    }
    else
        gtk_label_set_text (pricelabel, " ");

    if (categoriebool && etatbool && nombool && prixbool)
    {
        gtk_widget_hide (AddArticle);

        ARTICLE article;
        strcpy(article.categorie, categorie);
        g_free(categorie);

        strcpy(article.etat, etat);
        g_free(etat);

        strcpy(article.nom, nom);
        article.prix = prix;

        FILE *fp = fopen ("db/Article.dat","ab");
        fwrite (&article, sizeof(ARTICLE), 1, fp);
        fclose (fp);

        FILE *fp2 = fopen ("db/nbArticle.txt","r");
        int n=0;
        if (fp2 != NULL)
        {
            fscanf (fp2, "%d", &n);
            fclose (fp2);
        }


        FILE *fp3 = fopen ("db/nbArticle.txt", "w");
        fprintf (fp3, "%d", n+1);
        fclose (fp3);

        GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
        GtkTextIter iter;
        gtk_text_buffer_get_end_iter (textview, &iter);
        gchar text[200];
        sprintf(text, "\nArticle ajouter avec succès\ncategorie : %s\nNom : %s\netat : %s\nPrix : %d\n",
            article.categorie, article.nom, article.etat, article.prix);
        gtk_text_buffer_insert (textview, &iter, text, -1);

        gtk_combo_box_set_active (GTK_COMBO_BOX(categoriecombobox), -1);
        gtk_combo_box_set_active (GTK_COMBO_BOX(etatcombo), -1);
        gtk_label_set_text (categorylabel, " ");
        gtk_label_set_text (etatlabel, " ");
        gtk_label_set_text (namelabel, " ");
        gtk_label_set_text (pricelabel, " ");
        gtk_entry_set_text (nomarticle,  "Nom");
    }

}

void on_button4_clicked ()    
{
    gtk_widget_show(AddSalarie);
}

void on_button5_clicked ()    
{
    gtk_widget_show(AddFournisseur);
}

void on_button6_clicked ()    
{

    GtkComboBoxText  *categoriecombobox, *genrecombobox;
    GtkLabel         *categorylabel;
    categoriecombobox =  GTK_COMBO_BOX_TEXT (gtk_builder_get_object(builder, "comboboxtext3"));
    genrecombobox   =  GTK_COMBO_BOX_TEXT (gtk_builder_get_object(builder, "comboboxtext4"));
    categorylabel =  GTK_LABEL (gtk_builder_get_object(builder, "label22"));

    GtkEntry  *nomarticle;
    GtkLabel  *namelabel, *labeldepense;
    nomarticle   = GTK_ENTRY(gtk_builder_get_object(builder, "entry11"));
    GtkSpinButton *boutondepense = GTK_SPIN_BUTTON (gtk_builder_get_object(builder, "spinbutton1"));
    namelabel   = GTK_LABEL (gtk_builder_get_object(builder, "label24"));
    labeldepense = GTK_LABEL (gtk_builder_get_object(builder, "label23"));

    gchar *categorie = NULL;
    categorie = gtk_combo_box_text_get_active_text (categoriecombobox);
    gchar  *genre = gtk_combo_box_text_get_active_text (genrecombobox);

    const gchar *nom  = gtk_entry_get_text (nomarticle);
    int depense = gtk_spin_button_get_value_as_int (boutondepense);

    gboolean categoriebool = TRUE, nombool = TRUE, salairebool = TRUE;

    if (categorie == NULL)
    {
        gtk_label_set_text (categorylabel, "Erreur");
        categoriebool = FALSE;
    }
    else
        gtk_label_set_text (categorylabel, " ");

    if (strcmp(nom, "Nom") == 0)
    {
        gtk_label_set_text (namelabel, "Erreur");
        nombool = FALSE;
    }
    else
        gtk_label_set_text (namelabel, " ");

    if (depense == 0)
    {
        gtk_label_set_text (labeldepense, "Erreur");
        salairebool = FALSE;
    }
    else
        gtk_label_set_text (labeldepense, " ");

    if (categoriebool  && nombool && salairebool)
    {

        if (strcmp(categorie, "Vendeur") == 0)
        {
            gtk_widget_show(AddVendeurRayon);
        }

        gtk_widget_hide (AddSalarie);

        CLIENT clients;
        strcpy(clients.categorie, categorie);
        g_free(categorie);
        strcpy(clients.genre, genre);
        g_free(genre);

        strcpy(clients.nom, nom);
        clients.depense = depense;

        FILE *fp = fopen ("db/Client.dat","ab");
        fwrite (&clients, sizeof(CLIENT), 1, fp);
        fclose (fp);

        FILE *fp2 = fopen ("db/nbClient.txt","r");
        int n=0;
        if (fp2 != NULL)
        {
            fscanf (fp2, "%d", &n);
            fclose (fp2);
        }

        FILE *fp3 = fopen ("db/nbClient.txt", "w");
        fprintf (fp3, "%d", n+1);
        fclose (fp3);

        GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
        GtkTextIter iter;
        gtk_text_buffer_get_end_iter (textview, &iter);
        gchar text[200];
        sprintf(text, "\nClient ajouter avec succès\nCategorie : %s\nNom : %s\nGenre : %s\nDépense : %d\n",
                clients.categorie, clients.nom, clients.genre, clients.depense);
        gtk_text_buffer_insert (textview, &iter, text, -1);

        if (strcmp(clients.categorie, "VIP") == 0)
        {
            GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, "label29"));
            gtk_label_set_text (label, clients.nom);
        }

        gtk_combo_box_set_active (GTK_COMBO_BOX(categoriecombobox), -1);
        gtk_label_set_text (categorylabel, " ");
        gtk_label_set_text (namelabel, " ");
        gtk_label_set_text (labeldepense, " ");
        gtk_entry_set_text (nomarticle,  "Nom");
    }

}

void on_button7_clicked ()
{

    GtkSpinButton   *capacitybutton;
    GtkEntry        *nomarticle;
    GtkLabel        *capacitylabel, *namelabel;
    capacitybutton = GTK_SPIN_BUTTON (gtk_builder_get_object(builder, "spinbutton3"));
    nomarticle      = GTK_ENTRY (gtk_builder_get_object(builder, "entry14"));
    capacitylabel  = GTK_LABEL (gtk_builder_get_object(builder, "label25"));
    namelabel      = GTK_LABEL (gtk_builder_get_object(builder, "label26"));

    int capacite = gtk_spin_button_get_value_as_int (capacitybutton);
    const gchar *nom  = gtk_entry_get_text (nomarticle);

    gboolean capacitybool = TRUE, nombool = TRUE;

    if (capacite == 0)
    {
        gtk_label_set_text (capacitylabel, "Erreur");
        capacitybool = FALSE;
    }
    else
        gtk_label_set_text (capacitylabel, " ");

    if (strcmp(nom, "Nom") == 0)
    {
        gtk_label_set_text (namelabel, "Erreur");
        nombool = FALSE;
    }
    else
        gtk_label_set_text (namelabel, " ");

    if (capacitybool && nombool)
    {
        gtk_widget_hide (AddFournisseur);

        Fournisseur rayon;
        rayon.capacite = capacite;
        strcpy(rayon.nom, nom);
        strcpy(rayon.etat, "\0");
        strcpy(rayon.debut, "\0");
        strcpy(rayon.fin, "\0");

        FILE *fp = fopen ("db/Fournisseur.txt", "a");
        fwrite (&rayon, sizeof(Fournisseur), 1, fp);
        fclose (fp);

        FILE *fp2 = fopen ("db/nbFournisseur.txt","r");
        int n=0;
        if (fp2 != NULL)
        {
            fscanf (fp2, "%d", &n);
            fclose (fp2);
        }

        FILE *fp3 = fopen ("db/nbFournisseur.txt", "w");
        fprintf(fp3, "%d", n+1);
        fclose (fp3);

        GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
        GtkTextIter iter;
        gtk_text_buffer_get_end_iter (textview, &iter);
        gchar text[200];
        sprintf(text, "\nFournisseur ajouter avec succès\nNom : %s\nCapacité : %d\n",
            rayon.nom, rayon.capacite);
        gtk_text_buffer_insert (textview, &iter, text, -1);

        gtk_label_set_text (capacitylabel, " ");
        gtk_label_set_text (namelabel, " ");
        gtk_entry_set_text (nomarticle,  "Nom");
    }

}

void on_button8_clicked ()
{
      GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore1"));
      GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, "label29"));
      GtkTreeIter iter;
      gboolean value;
      gchar file[30];
      int counter=0;

      FILE *fp = fopen ("db/nbArticle.txt", "r");
      int n;
      fscanf (fp, "%d", &n);
      fclose (fp);

      gchar *b[n];
      gchar a[n][3];
      int i;
      for (i=0; i<n; i++)
          sprintf(a[i], "%d", i);

      for (i=0; i<n; i++)
          if ( gtk_tree_model_get_iter_from_string (model, &iter, a[i]))
          {
              gtk_tree_model_get (model, &iter, 1, &value, -1);
              if (value)
              {
                  gtk_tree_model_get (model, &iter, 0, &b[i], -1);
                  GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
                  GtkTextIter iter;
                  gtk_text_buffer_get_end_iter (textview, &iter);
                  gchar text[200];
                  sprintf(text, "\nCe client peut payer : %s\n", b[i]);
                  gtk_text_buffer_insert (textview, &iter, text, -1);
                  counter++;
              }
              else
                  b[i] = "\0";
          }

      if(counter == 0)
      {
            GtkLabel *label2 = GTK_LABEL(gtk_builder_get_object(builder, "label28"));
            gtk_label_set_text (label2, "Erreur");
      }

      else
      {
        int z=0;
        sprintf(file, "%s%s%s%s", "db/", "db/", gtk_label_get_text (label), ".txt");
        FILE *fp = fopen (file, "ab");
          for (i=0; i<n; i++)
              if (strcmp(b[i], "\0") != 0)
              {
                fprintf (fp, "%s\n", b[i]);
                z++;
              }

          sprintf(file, "%s%s%s%s%s", "db/", "db/", "nb", gtk_label_get_text (label), ".txt");
          FILE *fp2 = fopen (file, "wb");
          fprintf(fp2, "%d\n", z);
          fclose(fp2);
          fclose(fp);
          gtk_widget_hide (AddVendeurRayon);
      }

}

void on_button9_clicked ()
{
    FILE *fp = fopen ("db/nbArticle.txt", "r");
    if (fp == NULL)
    {
        GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
        GtkTextIter iter;
        gtk_text_buffer_get_end_iter (textview, &iter);
        gchar text[200];
        sprintf(text, "\nAjouter d'abord un article\n");
        gtk_text_buffer_insert (textview, &iter, text, -1);
        gtk_widget_hide(Commande);
    }
    else
    {
      gtk_widget_show(Commande);
      fclose(fp);
    }
    FILE *fp3 = fopen ("db/nbArticle.txt", "r");
    if (fp3 == NULL)
    {
        GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
        GtkTextIter iter;
        gtk_text_buffer_get_end_iter (textview, &iter);
        gchar text[200];
        sprintf(text, "\nAjouter un article\n");
        gtk_text_buffer_insert (textview, &iter, text, -1);
        gtk_widget_hide (Commande);
    }
    else
    {
      gtk_widget_show (Commande);
      fclose(fp3);
    }
    FILE *fp2 = fopen ("db/nbClient.txt", "r");
    if (fp2 == NULL)
    {
      GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
      GtkTextIter iter;
      gtk_text_buffer_get_end_iter (textview, &iter);
      gchar text[200];
      sprintf(text, "\nAjouter un client\n");
      gtk_text_buffer_insert (textview, &iter, text, -1);
        gtk_widget_hide (Commande);
    }
    else
    {
      gtk_widget_show (Commande);
      fclose(fp2);
    }

}

int  on_button10_clicked ()
{

    GDateTime *datetime = g_date_time_new_now_local ();
    char *Time;
    Time = g_date_time_format (datetime, "%F -- %T");

    gboolean tablebool = TRUE, waiterbool = TRUE, selectionbool = TRUE;

    GtkComboBoxText *tablecombo = GTK_COMBO_BOX_TEXT (gtk_builder_get_object(builder, "comboboxtext5"));
    GtkLabel        *tablelabel = GTK_LABEL (gtk_builder_get_object(builder, "label39"));
    gchar           *rayon      = gtk_combo_box_text_get_active_text (tablecombo);
    if (rayon == NULL)
    {
        gtk_label_set_text (tablelabel, "Erreur");
        tablebool = FALSE;
    }
    else
        gtk_label_set_text (tablelabel, " ");

    GtkComboBoxText *waitercombo = GTK_COMBO_BOX_TEXT (gtk_builder_get_object(builder, "comboboxtext6"));
    GtkLabel        *waiterlabel = GTK_LABEL (gtk_builder_get_object(builder, "label40"));
    gchar           *client      = gtk_combo_box_text_get_active_text (waitercombo);
    if (client == NULL)
    {
        gtk_label_set_text (waiterlabel, "Erreur");
        waiterbool = FALSE;
    }
    else
        gtk_label_set_text (waiterlabel, " ");

    GtkLabel        *Errorlabel = GTK_LABEL (gtk_builder_get_object(builder, "label41"));
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore2"));
    GtkTreeIter iter;
    gboolean value;

    FILE *fp = fopen ("db/nbArticle.txt", "r");
    int n;
    fscanf (fp, "%d", &n);
    fclose (fp);

    int z[n],c[n],counter=0;
    gchar *b[n][3];
    gchar text[n][100];

    gchar a[n][2];
    int i;
    for (i=0; i<n; i++)
        sprintf(a[i], "%d", i);

    for (i=0; i<n; i++)
        if ( gtk_tree_model_get_iter_from_string (model, &iter, a[i]))
        {
            gtk_tree_model_get (model, &iter, 0, &value, -1);
            if (value)
            {
                gtk_tree_model_get (model, &iter, 1, &b[i][0], -1);
                gtk_tree_model_get (model, &iter, 2, &b[i][1], -1);
                gtk_tree_model_get (model, &iter, 3, &z[i], -1);
                sprintf(text[i], "%s - %s - %d", b[i][0], b[i][1], z[i]);
                gtk_tree_model_get (model, &iter, 4, &c[i], -1);
                if (c[i] == 0)
                {
                    gtk_label_set_text (Errorlabel, "Erreur dans la selection de l'article");
                    selectionbool = FALSE;
                }
                else
                    gtk_label_set_text (Errorlabel, " ");
                gtk_tree_model_get (model, &iter, 5, &b[i][2], -1);
                if (b[i][2] == NULL)
                {
                    gtk_label_set_text (Errorlabel, "Erreur dans la selection de l'article");
                    selectionbool = FALSE;
                }
                else
                    gtk_label_set_text (Errorlabel, " ");
                counter++;
            }
        }

    if (counter == 0)
    {
          gtk_label_set_text (Errorlabel, "Erreur dans la selection de l'article");
          selectionbool = FALSE;
    }

    if (tablebool && waiterbool && selectionbool)
    {
        COMMANDE ClientCommande[counter];
        CLIENT client[counter];

        int w=0;
        for (i=0; i<n; i++)
          if ( gtk_tree_model_get_iter_from_string (model, &iter, a[i]))
          {
              gtk_tree_model_get (model, &iter, 0, &value, -1);
              if (value)
              {
                  strcpy(ClientCommande[w].temps, Time);
                  strcpy(ClientCommande[w].details, text[i]);
                  ClientCommande[w].numero = c[i];
                  ClientCommande[w].prix_total = c[i]*z[i];
                  {
                      gchar t[200];
                      sprintf(t, "%s%s%s", "db/db/nb", b[i][2], ".txt");
                      FILE *zp = fopen (t, "r");
                      int o=0;
                      fscanf(zp, "%d", &o);
                      fclose(zp);
                      sprintf(t, "%s%s%s", "db/db/", b[i][2], ".txt");
                      FILE *zp2 = fopen (t, "r");
                      int y;
                      gchar q[o][100];
                      for (y=0; y<o; y++)
                      {
                          fscanf(zp2, "%s\n", q[y]);
                      }
                      int dd=0;
                      for (y=0; y<o; y++)
                      {
                          if (strcmp(q[y], b[i][1]) == 0)
                          {
                              dd=1;
                          }
                          if (dd == 0)
                          {
                              gtk_label_set_text (Errorlabel, "Erreur dans la selection de l'article");
                              g_free (Time);
                              g_free (rayon);
                              g_free (client);
                              return 1;
                          }
                      }
                      fclose(zp2);
                  }
                  strcpy(ClientCommande[w].chef, b[i][2]);
                  strcpy(ClientCommande[w].client, client);
                  strcpy(ClientCommande[w].rayon, rayon);
                  strcpy(ClientCommande[w].etat, "En cours");

                  strcpy(client[w].categorie, "VIP");
                  strcpy(client[w].nom, ClientCommande[w].chef);

                  w++;
              }

          }

        COMMANDE ParentOrder;
        strcpy(ParentOrder.temps, Time);
        // strcpy( "Voir plus");
        ParentOrder.numero = counter;
        ParentOrder.prix_total = 0;
        for(i=0; i<counter; i++)
            ParentOrder.prix_total = ClientCommande[i].prix_total + ParentOrder.prix_total ;
        strcpy(ParentOrder.chef, "Voir plus");
        strcpy(ParentOrder.client, client);
        strcpy(ParentOrder.rayon, rayon);
        strcpy(ParentOrder.etat, "En cours");

        GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
        GtkTextIter iter2;
        gtk_text_buffer_get_end_iter (textview, &iter2);
        gchar textprint[20000];
        sprintf(textprint, "\nCommande ajouter avec succès\nHeure et date : %s\nQuantité : %d\nPrix Total : %d\nClient : %s\nWaiter : %s\netat : %s\n",
                ParentOrder.temps, ParentOrder.numero, ParentOrder.prix_total,
                ParentOrder.chef, ParentOrder.client, ParentOrder.etat);
        gtk_text_buffer_insert (textview, &iter2, textprint, -1);


        GtkTreeStore *store = GTK_TREE_STORE (gtk_builder_get_object(builder, "treestore1"));
        GtkTreeIter ParentIter, ChildIter;

        gtk_tree_store_append (store, &ParentIter, NULL);
        gtk_tree_store_set    (store, &ParentIter, 0, FALSE, 1, ParentOrder.temps,
                                2, ParentOrder.numero, 4, ParentOrder.prix_total,
                                5, ParentOrder.chef, 6, ParentOrder.client,
                                8, ParentOrder.etat, -1);
        for(i=0; i<counter; i++)
        {
            gtk_tree_store_append (store, &ChildIter, &ParentIter);
            gtk_tree_store_set    (store, &ChildIter, 0, FALSE, 1, ClientCommande[i].temps,
                                    2, ClientCommande[i].details, 3, ClientCommande[i].numero, 4, ClientCommande[i].prix_total,
                                    5, ClientCommande[i].chef, 6, ClientCommande[i].client, 7, ClientCommande[i].rayon,
                                    8, ClientCommande[i].etat, -1);
        }

        FILE *fp = fopen ("db/Commande.dat", "a");
        fwrite (&ParentOrder, sizeof(COMMANDE), 1, fp);
        fclose (fp);

        FILE *fp2 = fopen ("db/nbCommande.txt","r");
        int n=0;
        if (fp2 != NULL)
        {
            fscanf (fp2, "%d", &n);
            fclose (fp2);
        }

        FILE *fp3 = fopen ("db/nbCommande.txt", "w");
        fprintf(fp3, "%d", n+1);
        fclose (fp3);

        FILE *gp = fopen ("db/Commande.dat", "a");
        fwrite (&ClientCommande, sizeof(COMMANDE), counter, gp);
        fclose (gp);

        FILE *gp2 = fopen ("db/nbCommande.txt","r");
        fscanf (gp2, "%d", &n);
        fclose (gp2);

        FILE *gp3 = fopen ("db/nbCommande.txt", "w");
        fprintf(gp3, "%d", n+counter);
        fclose (gp3);

        VENDEUR onlinewaiter;
        strcpy(onlinewaiter.categorie, "NORMAL");
        strcpy(onlinewaiter.nom, client);
        strcpy(onlinewaiter.details, Time);
        strcpy(onlinewaiter.rayon, rayon);
        strcpy(onlinewaiter.etat, "En Cours");


        FILE *yp = fopen ("db/Client.dat", "a");
        fwrite (&onlinewaiter, sizeof(VENDEUR), 1, yp);
        fclose (yp);

        FILE *yp2 = fopen ("db/nbClient.txt","r");
        n=0;
        if (yp2 != NULL)
        {
            fscanf (fp2, "%d", &n);
            fclose (fp2);
        }

        FILE *yp3 = fopen ("db/nbClient.txt", "w");
        fprintf(yp3, "%d", n+1);
        fclose (yp3);

        FILE *zp = fopen ("db/Client.dat", "a");
        fwrite (&client, sizeof(COMMANDE), counter, zp);
        fclose (zp);

        FILE *zp2 = fopen ("db/nbClient.txt","r");
        fscanf (zp2, "%d", &n);
        fclose (zp2);

        FILE *zp3 = fopen ("db/nbClient.txt", "w");
        fprintf(zp3, "%d", n+1);
        fclose (zp3);

        GtkListStore *store5 = GTK_LIST_STORE (gtk_builder_get_object(builder, "liststore12"));
        GtkTreeIter iter;

        gtk_list_store_append (store5, &iter);
        gtk_list_store_set    (store5, &iter, 4, onlinewaiter.categorie, 0, onlinewaiter.nom,1, onlinewaiter.details,
                              3, onlinewaiter.rayon, 2, onlinewaiter.etat,-1);
        for(i=0; i<counter; i++)
        {
          gtk_list_store_append (store5, &iter);
          gtk_list_store_set    (store5, &iter, 4, client[i].categorie, 0, client[i].nom, -1);
        }


        gtk_widget_hide (Commande);
        g_free (Time);
        g_free (rayon);
        g_free (client);
    }
    return 0;
}

void on_button11_clicked ()
{
      GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore10"));
      GtkTreeIter iter;
      gboolean value;

      FILE *fp = fopen ("db/nbFournisseur.txt", "r");
      int n=0;
      fscanf (fp, "%d", &n);
      fclose (fp);

      FILE *fp2 = fopen ("db/Fournisseur.txt", "rb");
      Fournisseur rayon[n];
      fread (rayon, sizeof(Fournisseur), n, fp2);
      fclose(fp2);

      gchar *b;
      int z;
      int i;
      gchar a[n][2];

      for (i=0; i<n; i++)
          sprintf(a[i], "%d", i);

      for (i=0; i<n; i++)
          if ( gtk_tree_model_get_iter_from_string (model, &iter, a[i]))
          {
              gtk_tree_model_get (model, &iter, 0, &value, -1);
              if (value)
              {
                  gtk_tree_model_get (model, &iter, 1, &b, -1);
                  strcpy(rayon[i].nom, b);
                  gtk_tree_model_get (model, &iter, 2, &z, -1);
                  rayon[i].capacite = z;
                  gtk_tree_model_get (model, &iter, 3, &b, -1);
                  strcpy(rayon[i].etat, b);
                  gtk_tree_model_get (model, &iter, 4, &b, -1);
                  strcpy(rayon[i].debut, b);
                  gtk_tree_model_get (model, &iter, 5, &b, -1);
                  strcpy(rayon[i].fin, b);
                  GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
                  GtkTextIter iter;
                  gtk_text_buffer_get_end_iter (textview, &iter);
                  gchar text[200];
                  sprintf(text, "\nRayon modifier avec succès\nCapacité : %d\nNom : %s\n",
                          rayon[i].capacite, rayon[i].nom);
                  gtk_text_buffer_insert (textview, &iter, text, -1);
              }
          }

      FILE *fp3 = fopen ("db/Fournisseur.txt", "wb");
      fwrite (rayon, sizeof(Fournisseur), n, fp3);
      fclose(fp3);

      FILE *gp = fopen ("db/nbFournisseur.txt","r");
      int n1=0;
      fscanf (gp, "%d", &n1);
      fclose (gp);

      Fournisseur table2[n1];

      FILE *gp2 = fopen ("db/Fournisseur.txt", "r");
      fread (table2, sizeof(Fournisseur), n1, gp2);
      fclose (gp2);


      GtkListStore *store2 = GTK_LIST_STORE (gtk_builder_get_object(builder, "liststore13"));
      gtk_list_store_clear (store2);
      GtkTreeIter iter2;

      for (i=0; i<n1; i++)
      {
          if (strcmp(table2[i].etat, "Reservé maintenant") == 0 || strcmp(table2[i].etat, "Reservé après") == 0)
          {
              gtk_list_store_append (store2, &iter2);
              gtk_list_store_set    (store2, &iter2, 0, table2[i].nom, 1, table2[i].capacite,
                                            2, table2[i].etat, 3, table2[i].debut, 4, table2[i].fin, -1);
          }
      }

      gtk_widget_hide (ModifFournisseur);
}

void on_button12_clicked ()
{
      GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore7"));
      GtkTreeIter iter;
      gboolean value;

      FILE *fp = fopen ("db/nbClient.txt", "r");
      int n=0;
      fscanf (fp, "%d", &n);
      fclose (fp);

      FILE *fp2 = fopen ("db/Client.dat", "rb");
      CLIENT clients[n];
      fread (clients, sizeof(CLIENT), n, fp2);
      fclose(fp2);

      gchar *b;
      int z;
      int i;
      gchar a[n][2];

      for (i=0; i<n; i++)
          sprintf(a[i], "%d", i);

      for (i=0; i<n; i++)
          if ( gtk_tree_model_get_iter_from_string (model, &iter, a[i]))
          {
              gtk_tree_model_get (model, &iter, 0, &value, -1);
              if (value)
              {
                  gtk_tree_model_get (model, &iter, 1, &b, -1);
                  strcpy(clients[i].categorie, b);
                  gtk_tree_model_get (model, &iter, 2, &b, -1);
                  strcpy(clients[i].nom, b);
                  gtk_tree_model_get (model, &iter, 3, &z, -1);
                  clients[i].depense = z;
                  gtk_tree_model_get (model, &iter, 4, &b, -1);
                  strcpy(clients[i].genre, b);
                  GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
                  GtkTextIter iter;
                  gtk_text_buffer_get_end_iter (textview, &iter);
                  gchar text[200];
                  sprintf(text, "\nClient modifié avec succès \ncategorie : %s\nNom : %s\nGenre : %s\nDépense : %d\n",
                          clients[i].categorie, clients[i].nom, clients[i].genre, clients[i].depense);
                  gtk_text_buffer_insert (textview, &iter, text, -1);
              }
          }

      FILE *fp3 = fopen ("db/Client.dat", "wb");
      fwrite (clients, sizeof(CLIENT), n, fp3);
      fclose(fp3);

      gtk_widget_hide (ModifSalarie);
}

void on_button13_clicked ()
{
      GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore4"));
      GtkTreeIter iter;
      gboolean value;

      FILE *fp = fopen ("db/nbArticle.txt", "r");
      int n;
      fscanf (fp, "%d", &n);
      fclose (fp);

      FILE *fp2 = fopen ("db/Article.dat", "rb");
      ARTICLE article[n];
      fread (article, sizeof(ARTICLE), n, fp2);
      fclose(fp2);

      gchar *b;
      int z;
      int i;
      gchar a[n][2];

      for (i=0; i<n; i++)
          sprintf(a[i], "%d", i);

      for (i=0; i<n; i++)
          if ( gtk_tree_model_get_iter_from_string (model, &iter, a[i]))
          {
              gtk_tree_model_get (model, &iter, 0, &value, -1);
              if (value)
              {
                  gtk_tree_model_get (model, &iter, 1, &b, -1);
                  strcpy(article[i].categorie, b);
                  gtk_tree_model_get (model, &iter, 2, &b, -1);
                  strcpy(article[i].nom, b);
                  gtk_tree_model_get (model, &iter, 3, &z, -1);
                  article[i].prix = z;
                  gtk_tree_model_get (model, &iter, 4, &b, -1);
                  strcpy(article[i].etat, b);
                  GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
                  GtkTextIter iter;
                  gtk_text_buffer_get_end_iter (textview, &iter);
                  gchar text[200];
                  sprintf(text, "\nArticle modifier avec succès\nCategorie : %s\nNom : %s\netat : %s\nPrix : %d\n",
                          article[i].categorie, article[i].nom, article[i].etat, article[i].prix);
                  gtk_text_buffer_insert (textview, &iter, text, -1);
              }
          }

      FILE *fp3 = fopen ("db/Article.dat", "wb");
      fwrite (article, sizeof(ARTICLE), n, fp3);
      fclose(fp3);

      gtk_widget_hide (ModifArticle);

}

void on_button14_clicked ()
{
    ModifArticle = GTK_WIDGET (gtk_builder_get_object (builder, "ModifArticle"));
    FILE *fp = fopen ("db/nbArticle.txt", "r");
    if (fp == NULL)
    {
      GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
      GtkTextIter iter;
      gtk_text_buffer_get_end_iter (textview, &iter);
      gchar text[200];
      sprintf(text, "\nAjouter un article d'abord\n");
      gtk_text_buffer_insert (textview, &iter, text, -1);
        gtk_widget_hide (ModifArticle);
    }
    else
    {
      gtk_widget_show (ModifArticle);
      fclose(fp);
    }
}

void on_button15_clicked ()
{
    ModifSalarie = GTK_WIDGET (gtk_builder_get_object (builder, "ModifSalarie"));
    FILE *fp = fopen ("db/nbClient.txt", "r");
    if (fp == NULL)
    {
      GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
      GtkTextIter iter;
      gtk_text_buffer_get_end_iter (textview, &iter);
      gchar text[200];
      sprintf(text, "\nAjouter un client svp\n");
      gtk_text_buffer_insert (textview, &iter, text, -1);
        gtk_widget_hide (ModifSalarie);
    }
    else
    {
      fclose(fp);
      gtk_widget_show (ModifSalarie);
    }

}

void on_button16_clicked ()
{
    ModifFournisseur = GTK_WIDGET (gtk_builder_get_object (builder, "ModifFournisseur"));
    FILE *fp = fopen ("db/nbFournisseur.txt", "r");
    if (fp == NULL)
    {
      GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
      GtkTextIter iter;
      gtk_text_buffer_get_end_iter (textview, &iter);
      gchar text[200];
      sprintf(text, "\nAjouter d'abord un fournisseur\n");
      gtk_text_buffer_insert (textview, &iter, text, -1);
        gtk_widget_hide (ModifFournisseur);
    }
    else
    {
      gtk_widget_show (ModifFournisseur);
      fclose(fp);
    }
}

void on_button17_clicked ()   // Fait a Reserve
{
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "treestore1"));
    GtkTreeIter iter, iter2;
    gtk_tree_model_get_iter_first (model, &iter);
    gboolean value;

    FILE *fp = fopen ("db/nbCommande.txt", "r");
    int n;
    fscanf (fp, "%d", &n);
    fclose (fp);

    FILE *fp2 = fopen ("db/Commande.dat", "rb");
    COMMANDE order[n];
    fread (order, sizeof(COMMANDE), n, fp2);
    fclose(fp2);

    int w=0;
    do
    {
            gtk_tree_model_get (model, &iter, 0, &value, -1);
            if (value)
            {
                strcpy(order[w].etat, "Fait");
                GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
                GtkTextIter iter3;
                gtk_text_buffer_get_end_iter (textview, &iter3);
                gchar text[200];
                sprintf(text, "\nCommande passer avec succès\n");
                gtk_text_buffer_insert (textview, &iter3, text, -1);
                w++;
                if (gtk_tree_model_iter_children (model, &iter2, &iter))
                {
                    do
                    {
                        strcpy(order[w].etat, "Fait");
                        w++;

                    } while (gtk_tree_model_iter_next (model, &iter2));
                }
            }
            else
                w = w + gtk_tree_model_iter_n_children (model, &iter) + 1;

    } while (gtk_tree_model_iter_next (model, &iter));

    FILE *gp2 = fopen ("db/Commande.dat", "wb");
    fwrite (order, sizeof(COMMANDE), n, gp2);
    fclose(gp2);

    FILE *fp11 = fopen ("db/nbCommande.txt", "r");
    fscanf (fp11, "%d", &n);
    fclose (fp11);

    FILE *fp6 = fopen ("db/Commande.dat", "rb");
    COMMANDE order2[n];
    fread (&order2, sizeof(COMMANDE), n, fp6);
    fclose (fp6);

    GtkTreeStore *store = GTK_TREE_STORE (gtk_builder_get_object(builder, "treestore1"));
    gtk_tree_store_clear (store);
    GtkTreeIter ParentIter, ChildIter;
    int i;
    for (i=0; i<n; i++)
    {
          if (strcmp(order2[i].details, "Voir plus") == 0)
          {
              gtk_tree_store_append (store, &ParentIter, NULL);
              gtk_tree_store_set    (store, &ParentIter, 0, FALSE, 1, order2[i].temps,
                                      2, order2[i].details, 3, order2[i].numero, 4, order2[i].prix_total,
                                      5, order2[i].chef, 6, order2[i].client, 7, order2[i].rayon,
                                      8, order2[i].etat, -1);
          }
          else
          {
              gtk_tree_store_append (store, &ChildIter, &ParentIter);
              gtk_tree_store_set    (store, &ChildIter, 0, FALSE, 1, order2[i].temps,
                                      2, order2[i].details, 3, order2[i].numero, 4, order2[i].prix_total,
                                      5, order2[i].chef, 6, order2[i].client, 7, order2[i].rayon,
                                      8, order2[i].etat, -1);
          }
    }

}

/******************************************************************************/

void on_cellrendererspin1_edited (GtkCellRendererSpin *renderer, gchar *path)
{
      GtkTreeIter iter;
      GtkTreeModel *model;
      GtkAdjustment *adjustment;
      gint value;

      model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore2"));
      adjustment = GTK_ADJUSTMENT (gtk_builder_get_object(builder, "adjustment1"));
      value = gtk_adjustment_get_value (adjustment);

      if (gtk_tree_model_get_iter_from_string (model, &iter, path))
          gtk_list_store_set (GTK_LIST_STORE (model), &iter, 4, value, -1);
}

void on_cellrendererspin2_edited (GtkCellRendererSpin *renderer, gchar *path)
{
      GtkTreeIter iter;
      GtkTreeModel *model;
      GtkAdjustment *adjustment;
      gint value;

      model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore4"));
      adjustment = GTK_ADJUSTMENT (gtk_builder_get_object(builder, "adjustment1"));
      value = gtk_adjustment_get_value (adjustment);

      if (gtk_tree_model_get_iter_from_string (model, &iter, path))
          gtk_list_store_set (GTK_LIST_STORE (model), &iter, 3, value, -1);
}

void on_cellrendererspin4_edited (GtkCellRendererSpin *renderer, gchar *path)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkAdjustment *adjustment;
    gint value;

    model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore10"));
    adjustment = GTK_ADJUSTMENT (gtk_builder_get_object(builder, "adjustment1"));
    value = gtk_adjustment_get_value (adjustment);

    if (gtk_tree_model_get_iter_from_string (model, &iter, path))
        gtk_list_store_set (GTK_LIST_STORE (model), &iter, 2, value, -1);
}

void on_cellrendererspin3_edited (GtkCellRendererSpin *renderer, gchar *path)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkAdjustment *adjustment;
    gint value;

    model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore7"));
    adjustment = GTK_ADJUSTMENT (gtk_builder_get_object(builder, "adjustment1"));
    value = gtk_adjustment_get_value (adjustment);

    if (gtk_tree_model_get_iter_from_string (model, &iter, path))
        gtk_list_store_set (GTK_LIST_STORE (model), &iter, 3, value, -1);
}

/******************************************************************************/

void on_cellrenderercombo1_edited (GtkCellRendererText *renderer, gchar *path, gchar *new_text)
{

    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore2"));

      if (gtk_tree_model_get_iter_from_string (model, &iter, path))
            gtk_list_store_set (GTK_LIST_STORE (model), &iter, 5, new_text, -1);
}

void on_cellrenderercombo2_edited (GtkCellRendererText *renderer, gchar *path, gchar *new_text)
{
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore4"));

      if (gtk_tree_model_get_iter_from_string (model, &iter, path))
            gtk_list_store_set (GTK_LIST_STORE (model), &iter, 4, new_text, -1);
}

void on_cellrenderercombo3_edited (GtkCellRendererText *renderer, gchar *path, gchar *new_text)
{
      GtkTreeIter iter;
      GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore4"));

        if (gtk_tree_model_get_iter_from_string (model, &iter, path))
              gtk_list_store_set (GTK_LIST_STORE (model), &iter, 1, new_text, -1);
}

void on_cellrenderercombo4_edited (GtkCellRendererText *renderer, gchar *path, gchar *new_text)
{
      GtkTreeIter iter;
      GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore7"));

        if (gtk_tree_model_get_iter_from_string (model, &iter, path))
              gtk_list_store_set (GTK_LIST_STORE (model), &iter, 1, new_text, -1);
}

void on_cellrenderercombo5_edited (GtkCellRendererText *renderer, gchar *path, gchar *new_text)
{
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore7"));

      if (gtk_tree_model_get_iter_from_string (model, &iter, path))
            gtk_list_store_set (GTK_LIST_STORE (model), &iter, 4, new_text, -1);
  }

void on_cellrenderercombo34_edited (GtkCellRendererText *renderer, gchar *path, gchar *new_text)
{
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore10"));

      if (gtk_tree_model_get_iter_from_string (model, &iter, path))
            gtk_list_store_set (GTK_LIST_STORE (model), &iter, 3, new_text, -1);
}

/******************************************************************************/

void on_cellrenderertext5_edited (GtkCellRendererText *renderer, gchar *path, gchar *new_text)
{
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore7"));

      if (gtk_tree_model_get_iter_from_string (model, &iter, path))
            gtk_list_store_set (GTK_LIST_STORE (model), &iter, 2, new_text, -1);
}

void on_cellrenderertext6_edited (GtkCellRendererText *renderer, gchar *path, gchar *new_text)
{
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore4"));

      if (gtk_tree_model_get_iter_from_string (model, &iter, path))
            gtk_list_store_set (GTK_LIST_STORE (model), &iter, 2, new_text, -1);
}

void on_cellrenderertext7_edited (GtkCellRendererText *renderer, gchar *path, gchar *new_text)
{
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore10"));

      if (gtk_tree_model_get_iter_from_string (model, &iter, path))
            gtk_list_store_set (GTK_LIST_STORE (model), &iter, 1, new_text, -1);
}

void on_cellrenderertext35_edited (GtkCellRendererText *renderer, gchar *path, gchar *new_text)
{
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore10"));

      if (gtk_tree_model_get_iter_from_string (model, &iter, path))
            gtk_list_store_set (GTK_LIST_STORE (model), &iter, 4, new_text, -1);
}

void on_cellrenderertext36_edited (GtkCellRendererText *renderer, gchar *path, gchar *new_text)
{
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore10"));

      if (gtk_tree_model_get_iter_from_string (model, &iter, path))
            gtk_list_store_set (GTK_LIST_STORE (model), &iter, 5, new_text, -1);
}

/******************************************************************************/

void on_cellrenderertoggle1_toggled (GtkCellRendererToggle *renderer, gchar *path)
{

      GtkTreeIter iter;
      gboolean value;
      GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore1"));

      if (gtk_tree_model_get_iter_from_string (model, &iter, path))
      {
          gtk_tree_model_get (model, &iter, 1, &value, -1);
          gtk_list_store_set (GTK_LIST_STORE (model), &iter, 1, !value, -1);
      }

}

void on_cellrenderertoggle2_toggled (GtkCellRendererToggle *renderer, gchar *path)
{

      GtkTreeIter iter;
      gboolean value;
      GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore2"));

      if (gtk_tree_model_get_iter_from_string (model, &iter, path))
      {
          gtk_tree_model_get (model, &iter, 0, &value, -1);
          gtk_list_store_set (GTK_LIST_STORE (model), &iter, 0, !value, -1);
      }
}

void on_cellrenderertoggle3_toggled (GtkCellRendererToggle *renderer, gchar *path)
{
      GtkTreeIter iter;
      gboolean value;
      GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore4"));

      if (gtk_tree_model_get_iter_from_string (model, &iter, path))
      {
          gtk_tree_model_get (model, &iter, 0, &value, -1);
          gtk_list_store_set (GTK_LIST_STORE (model), &iter, 0, !value, -1);
      }
}

void on_cellrenderertoggle4_toggled (GtkCellRendererToggle *renderer, gchar *path)
{
    GtkTreeIter iter;
    gboolean value;
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore7"));

    if (gtk_tree_model_get_iter_from_string (model, &iter, path))
    {
        gtk_tree_model_get (model, &iter, 0, &value, -1);
        gtk_list_store_set (GTK_LIST_STORE (model), &iter, 0, !value, -1);
    }
}

void on_cellrenderertoggle5_toggled (GtkCellRendererToggle *renderer, gchar *path)
{
    GtkTreeIter iter;
    gboolean value;
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore10"));

    if (gtk_tree_model_get_iter_from_string (model, &iter, path))
    {
        gtk_tree_model_get (model, &iter, 0, &value, -1);
        gtk_list_store_set (GTK_LIST_STORE (model), &iter, 0, !value, -1);
    }
}

void on_cellrenderertoggle6_toggled (GtkCellRendererToggle *renderer, gchar *path)
{
    GtkTreeIter ParentIter, ChildIter;
    gboolean value;
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "treestore1"));

    if (strlen(path) == 1 || strlen(path) == 2)
        if (gtk_tree_model_get_iter_from_string (model, &ParentIter, path))
        {
            gtk_tree_model_get (GTK_TREE_MODEL(model), &ParentIter, 0, &value, -1);
            gtk_tree_store_set (GTK_TREE_STORE(model), &ParentIter, 0 , !value, -1);
            if (gtk_tree_model_iter_children (model, &ChildIter, &ParentIter))
            do
            {
                gtk_tree_store_set (GTK_TREE_STORE(model), &ChildIter, 0 , !value, -1);

            }   while (gtk_tree_model_iter_next (model, &ChildIter));

        }

    if (strlen(path) == 3 || strlen(path) == 4)
    {
        if (gtk_tree_model_get_iter_from_string (model, &ChildIter, path))
        {
            gtk_tree_model_get (GTK_TREE_MODEL(model), &ChildIter, 0, &value, -1);
            gtk_tree_store_set (GTK_TREE_STORE(model), &ChildIter, 0 , !value, -1);
            gtk_tree_model_iter_parent (model, &ParentIter, &ChildIter);
            gtk_tree_store_set (GTK_TREE_STORE(model), &ParentIter, 0 , FALSE, -1);
        }
    }


}

/******************************************************************************/

void on_MainWindow_show ()
{

    FILE *fp = fopen ("db/nbCommande.txt","r");
    int n=0;
    if (fp != NULL)
    {
      fscanf (fp, "%d", &n);
      fclose (fp);
      COMMANDE order[n];

      FILE *fp2 = fopen ("db/Commande.dat", "r");
      fread (&order, sizeof(COMMANDE), n, fp2);
      fclose (fp2);


      GtkTreeStore *store = GTK_TREE_STORE (gtk_builder_get_object(builder, "treestore1"));
      gtk_tree_store_clear (store);
      GtkTreeIter ParentIter, ChildIter;
      int i;
      for (i=0; i<n; i++)
      {
          if (strcmp(order[i].details, "Voir plus") == 0)
          {
              gtk_tree_store_append (store, &ParentIter, NULL);
              gtk_tree_store_set    (store, &ParentIter, 0, FALSE, 1, order[i].temps,
                                      2, order[i].details, 3, order[i].numero, 4, order[i].prix_total,
                                      5, order[i].chef, 6, order[i].client, 7, order[i].rayon,
                                      8, order[i].etat, -1);
          }
          else
          {
              gtk_tree_store_append (store, &ChildIter, &ParentIter);
              gtk_tree_store_set    (store, &ChildIter, 0, FALSE, 1, order[i].temps,
                                      2, order[i].details, 3, order[i].numero, 4, order[i].prix_total,
                                      5, order[i].chef, 6, order[i].client, 7, order[i].rayon,
                                      8, order[i].etat, -1);
          }
      }


      FILE *gp = fopen ("db/nbFournisseur.txt","r");
      n=0;
      if (fp != NULL)
      {
        fscanf (gp, "%d", &n);
        fclose (gp);
      }

      Fournisseur rayon[n];

      FILE *gp2 = fopen ("db/Fournisseur.txt", "r");
      fread (rayon, sizeof(Fournisseur), n, gp2);
      fclose (gp2);


      GtkListStore *store2 = GTK_LIST_STORE (gtk_builder_get_object(builder, "liststore13"));
      gtk_list_store_clear (store2);
      GtkTreeIter iter;

      for (i=0; i<n; i++)
      {
          if (strcmp(rayon[i].etat, "Reservé maintenant") == 0 || strcmp(rayon[i].etat, "Reservé après") == 0)
          {
              gtk_list_store_append (store2, &iter);
              gtk_list_store_set    (store2, &iter, 0, rayon[i].nom, 1, rayon[i].capacite,
                                      2, rayon[i].etat, 3, rayon[i].debut, 4, rayon[i].fin, -1);
          }
      }
    }

    GtkListStore *store5 = GTK_LIST_STORE (gtk_builder_get_object(builder, "liststore12"));
    GtkTreeIter iter5;

    FILE *zp2 = fopen ("db/nbVendeur.txt", "r");
    n=0;
    if (zp2 != NULL)
    {
        fscanf (zp2, "%d", &n);
        fclose (zp2);
        VENDEUR online[n];

        FILE *zp3 = fopen ("db/VENDEUR.dat", "rb");
        fread (online, sizeof(VENDEUR), n, zp3);
        fclose (zp3);

        int i;
        for(i=0; i<n; i++)
        {
          gtk_list_store_append (store5, &iter5);
          gtk_list_store_set    (store5, &iter5, 4, online[i].categorie, 0, online[i].nom,1, online[i].details,
                                  3, online[i].rayon, 2, online[i].etat, -1);
        }
    }


}

void on_ResevationWindow_show ()
{
    GtkListStore *store = GTK_LIST_STORE (gtk_builder_get_object(builder, "liststore2"));
    GtkTreeIter   iter, iter2;
    gtk_list_store_clear (store);

    GtkCellRenderer *renderer2 = GTK_CELL_RENDERER (gtk_builder_get_object(builder, "cellrenderercombo1"));
    GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore3"));
    gtk_list_store_clear (GTK_LIST_STORE(model));
    g_object_set (renderer2, "text-column", 0, "editable", TRUE, "has-entry", TRUE, "model", model, NULL);

    GtkCellRenderer *renderer;
    GtkAdjustment *adj;
    adj = GTK_ADJUSTMENT (gtk_builder_get_object(builder, "adjustment1"));
    renderer = GTK_CELL_RENDERER (gtk_builder_get_object(builder, "cellrendererspin1"));
    g_object_set (renderer, "editable", TRUE, "adjustment", adj, "digits", 0, NULL);

    FILE *fp = fopen ("db/nbArticle.txt", "r");
    int n=0;
    fscanf (fp, "%d", &n);
    fclose (fp);

    FILE *fp2 = fopen ("db/Article.dat", "rb");
    ARTICLE article[n];
    fread (article, sizeof(ARTICLE), n, fp2);
    fclose(fp2);

    int i;
    for (i=0; i<n; i++)
    {
        if (strcmp(article[i].etat, "Disponible") == 0)
        {
          gtk_list_store_append (store, &iter);
          gtk_list_store_set (store, &iter, 0, FALSE, 1, article[i].categorie, 2,
              article[i].nom, 3, article[i].prix, -1);
        }
    }

    FILE *pp = fopen ("db/nbClient.txt", "r");
    fscanf (pp, "%d", &n);
    fclose (pp);

    FILE *pp2 = fopen ("db/Peoples.dat", "rb");
    CLIENT clients[n];
    fread (clients, sizeof(CLIENT), n, pp2);
    fclose(pp2);

    GtkComboBoxText *waitercombo = GTK_COMBO_BOX_TEXT (gtk_builder_get_object(builder, "comboboxtext6"));
    gtk_combo_box_text_remove_all (waitercombo);

    for (i=0; i<n; i++)
    {
        if (strcmp(clients[i].categorie, "Vendeur") == 0)
        {
            gtk_list_store_append (GTK_LIST_STORE(model), &iter2);
            gtk_list_store_set (GTK_LIST_STORE(model), &iter2, 0, clients[i].nom, -1);
        }
        if (strcmp(clients[i].categorie, "Assistant") == 0 || strcmp(clients[i].categorie, "Caissière") == 0)
            gtk_combo_box_text_insert_text (waitercombo, i, clients[i].nom);
    }

    GtkComboBoxText *tablecombo = GTK_COMBO_BOX_TEXT (gtk_builder_get_object (builder, "comboboxtext5"));
    gtk_combo_box_text_remove_all (tablecombo);

    FILE *gp = fopen ("db/nbFournisseur.txt", "r");
    fscanf (gp, "%d", &n);
    fclose (gp);

    FILE *gp2 = fopen ("db/Fournisseur.txt", "rb");
    Fournisseur rayon[n];
    fread (rayon, sizeof(Fournisseur), n, gp2);
    fclose(gp2);

    char text[30];

    for (i=0; i<n; i++)
    {
          if (strcmp(rayon[i].etat, "Reservé maintenant") != 0)
          {
            sprintf (text, "%s%s%d", rayon[i].nom, " -> ", rayon[i].capacite);
            gtk_combo_box_text_insert_text (tablecombo, i, text);
          }

    }


}

void on_AddPeopleWindow_show ()
{
    FILE *fp = fopen ("db/nbArticle.txt", "r");
    if (fp != NULL)
        fclose (fp);
    else
    {
      GtkTextBuffer *textview = GTK_TEXT_BUFFER (gtk_builder_get_object(builder, "textbuffer1"));
      GtkTextIter iter;
      gtk_text_buffer_get_end_iter (textview, &iter);
      gchar text[200];
      sprintf(text, "\nAjouter un article svp :\n");
      gtk_text_buffer_insert (textview, &iter, text, -1);
        gtk_widget_hide (AddSalarie);
    }
}

void on_AddChefAbility_show ()
{
    GtkListStore *store = GTK_LIST_STORE (gtk_builder_get_object(builder, "liststore1"));
    GtkTreeIter   iter;
    gtk_list_store_clear (store);

    FILE *fp = fopen ("db/nbArticle.txt", "r");
    int n=0;
    fscanf (fp, "%d", &n);
    fclose (fp);

    FILE *fp2 = fopen ("db/Article.dat", "rb");
    ARTICLE article[n];
    fread (article, sizeof(ARTICLE), n, fp2);
    fclose(fp2);

    int i;
    for (i=0; i<n; i++)
    {
        gtk_list_store_append (store, &iter);
        gtk_list_store_set (store, &iter, 1, FALSE, 0, article[i].nom, -1);
    }
}

void on_EditTableWindow_show ()
{

    FILE *fp = fopen ("db/nbFournisseur.txt", "r");
    int n=0;
    if (fp != NULL)
    {
      fscanf (fp, "%d", &n);
      fclose (fp);
      GtkListStore *store = GTK_LIST_STORE (gtk_builder_get_object(builder, "liststore10"));
      GtkTreeIter   iter;
      gtk_list_store_clear (store);

      GtkCellRenderer *renderer;
      GtkAdjustment *adj;
      adj = GTK_ADJUSTMENT (gtk_builder_get_object(builder, "adjustment1"));
      renderer = GTK_CELL_RENDERER (gtk_builder_get_object(builder, "cellrendererspin4"));
      g_object_set (renderer, "editable", TRUE, "adjustment", adj, "digits", 0, NULL);

      GtkCellRenderer *renderer2 = GTK_CELL_RENDERER (gtk_builder_get_object(builder, "cellrenderercombo34"));
      GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore11"));
      g_object_set (renderer2, "text-column", 0, "editable", TRUE, "has-entry", TRUE, "model", model, NULL);

      FILE *fp2 = fopen ("db/Fournisseur.txt", "rb");
      Fournisseur rayon[n];
      fread (rayon, sizeof(Fournisseur), n, fp2);
      fclose(fp2);

      int i;
      for (i=0; i<n; i++)
      {
          gtk_list_store_append (store, &iter);
          gtk_list_store_set (store, &iter, 0, FALSE, 1, rayon[i].nom, 2, rayon[i].capacite,
                              3, rayon[i].etat, 4, rayon[i].debut, 5, rayon[i].fin, -1);

      }
    }

}

void on_EditFoodWindow_show ()
{

      FILE *fp = fopen ("db/nbArticle.txt", "r");
      int n=0;
      if (fp != NULL)
      {
        fscanf (fp, "%d", &n);
        fclose (fp);
        GtkListStore *store = GTK_LIST_STORE (gtk_builder_get_object(builder, "liststore4"));
        GtkTreeIter   iter;
        gtk_list_store_clear (store);

        GtkCellRenderer *renderer2 = GTK_CELL_RENDERER (gtk_builder_get_object(builder, "cellrenderercombo2"));
        GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore5"));
        g_object_set (renderer2, "text-column", 0, "editable", TRUE, "has-entry", TRUE, "model", model, NULL);

        GtkCellRenderer *renderer3 = GTK_CELL_RENDERER (gtk_builder_get_object(builder, "cellrenderercombo3"));
        GtkTreeModel *model1 = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore6"));
        g_object_set (renderer3, "text-column", 0, "editable", TRUE, "has-entry", TRUE, "model", model1, NULL);


        GtkCellRenderer *renderer;
        GtkAdjustment *adj;
        adj = GTK_ADJUSTMENT (gtk_builder_get_object(builder, "adjustment1"));
        renderer = GTK_CELL_RENDERER (gtk_builder_get_object(builder, "cellrendererspin2"));
        g_object_set (renderer, "editable", TRUE, "adjustment", adj, "digits", 0, NULL);

        FILE *fp2 = fopen ("db/Article.dat", "rb");
        ARTICLE article[n];
        fread (article, sizeof(ARTICLE), n, fp2);
        fclose(fp2);

        int i;
        for (i=0; i<n; i++)
        {
            gtk_list_store_append (store, &iter);
            gtk_list_store_set (store, &iter, 0, FALSE, 1, article[i].categorie, 2,
                article[i].nom, 3, article[i].prix, 4, article[i].etat, -1);

        }
      }
}

void on_EdotPeopleWindow_show ()
{

      FILE *fp = fopen ("db/nbClient.txt", "r");
      int n=0;
      if (fp != NULL)
      {
        fscanf (fp, "%d", &n);
        fclose (fp);
        GtkListStore *store = GTK_LIST_STORE (gtk_builder_get_object(builder, "liststore7"));
        GtkTreeIter   iter;
        gtk_list_store_clear (store);

        GtkCellRenderer *renderer2 = GTK_CELL_RENDERER (gtk_builder_get_object(builder, "cellrenderercombo4"));
        GtkTreeModel *model = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore8"));
        g_object_set (renderer2, "text-column", 0, "editable", TRUE, "has-entry", TRUE, "model", model, NULL);

        GtkCellRenderer *renderer3 = GTK_CELL_RENDERER (gtk_builder_get_object(builder, "cellrenderercombo5"));
        GtkTreeModel *model2 = GTK_TREE_MODEL (gtk_builder_get_object(builder, "liststore9"));
        g_object_set (renderer3, "text-column", 0, "editable", TRUE, "has-entry", TRUE, "model", model2, NULL);

        GtkCellRenderer *renderer;
        GtkAdjustment *adj;
        adj = GTK_ADJUSTMENT (gtk_builder_get_object(builder, "adjustment1"));
        renderer = GTK_CELL_RENDERER (gtk_builder_get_object(builder, "cellrendererspin3"));
        g_object_set (renderer, "editable", TRUE, "adjustment", adj, "digits", 0, NULL);

        FILE *fp2 = fopen ("db/Client.dat", "rb");
        CLIENT clients[n];
        fread (clients, sizeof(CLIENT), n, fp2);
        fclose(fp2);

        int i;
        for (i=0; i<n; i++)
        {
            gtk_list_store_append (store, &iter);
            gtk_list_store_set (store, &iter, 0, FALSE, 1, clients[i].categorie, 2,
                clients[i].nom, 3, clients[i].depense, 4, clients[i].genre, -1);

        }
      }
}

/******************************************************************************/

void on_imagemenuitem10_activate ()
{
    GtkWidget *about = GTK_WIDGET (gtk_builder_get_object (builder, "aboutdialog1"));
    gtk_widget_show (about);
}

/******************************************************************************/

int main (int argc, char *argv[])
{

    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file ("GUI.glade");
    gtk_builder_connect_signals(builder, NULL);

    PageConnexion = GTK_WINDOW(gtk_builder_get_object(builder, "PageConnexion"));
    Principale  = GTK_WINDOW(gtk_builder_get_object(builder, "Principale"));
    AddArticle = GTK_WIDGET(gtk_builder_get_object(builder, "AddArticle"));
    AddSalarie = GTK_WIDGET(gtk_builder_get_object(builder, "AddSalarie"));
    AddFournisseur = GTK_WIDGET(gtk_builder_get_object(builder, "AddFournisseur"));
    AddVendeurRayon = GTK_WIDGET(gtk_builder_get_object(builder, "AddVendeurRayon"));
    Commande  = GTK_WIDGET(gtk_builder_get_object(builder, "Commande"));

    gtk_widget_hide (GTK_WIDGET(AddArticle));
    gtk_widget_hide (GTK_WIDGET(AddSalarie));
    gtk_widget_hide (GTK_WIDGET(AddFournisseur));
    gtk_widget_hide (GTK_WIDGET(Principale));
    gtk_widget_hide (GTK_WIDGET(PageConnexion));
    gtk_widget_hide (GTK_WIDGET(AddVendeurRayon));
    gtk_widget_hide (GTK_WIDGET(Commande));

    GtkLabel *TimeLabel = GTK_LABEL (gtk_builder_get_object(builder, "label32"));
    GDateTime *datetime = g_date_time_new_now_local ();
    char *Time;
    Time = g_date_time_format (datetime, "%T -- %F");
    gtk_label_set_text (TimeLabel, Time);
    g_free(Time);

    FILE *AlvielInfo;
    AlvielInfo = fopen ("db/AlvielInfo.txt","r");
    if(AlvielInfo == NULL)
    {
        gtk_widget_show (GTK_WIDGET(PageConnexion));
    }

    else
    {
        gtk_widget_show (GTK_WIDGET(Principale));
        gchar a[20];
        fscanf(AlvielInfo, "%s\n", a);
        gtk_window_set_title (Principale, a);
        fclose(AlvielInfo);
    }

    gtk_main();

    return 0;
}