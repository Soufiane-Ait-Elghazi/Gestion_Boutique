----------------------------------- GESTION DE BOUTIQUE --------------------------------

use Gestion_Boutique
------------------------------
select * from CLIENT
select * from LIGNECOMMANDE
select * from FACTURE	
select * from PRODUIT
select * from FOURNISSEUR
select * from FOURNIR
select * from CATEGORIE
go
-----------------------------------------------------------------------------------------
------------------------ les clients d'une ville donnée ---------------------------------
 create procedure ps_client_ville_donne
  @ville_donnee as nvarchar(12)
	as
	begin
		select * from CLIENT
			where VilleClient = @ville_donnee
	end
	exec ps_client_ville_donne 'ERRACHIDIA'
	go
 --------------------------- le nombre de clients total ------------------------------------
 create procedure ps_nombre_client_total
	as
	begin
	select count(IdClient) as nombre_clients_total
		from CLIENT
	end
	exec ps_nombre_client_total
	go
 ----------------------------- le nombre de clients d'une ville donnee ------------------------
 create procedure ps_nombre_client_ville_donnee
  @ville_donnee as nvarchar(12)
	as 
	begin
		select count(IdClient) as nombre_clients_ville_donnee  from CLIENT
			where VilleClient = @ville_donnee
	end
	exec ps_nombre_client_ville_donnee 'ERRACHIDIA'
	go
--------------------------------- le nombre de clients par ville -------------------------------
create procedure ps_nombre_client_par_ville
	as
	begin
		select VilleClient,count(IdClient) as nombre_clients_par_ville
			from CLIENT
			group by VilleClient
	end
	exec ps_nombre_client_par_ville
	go
--------------------------------- ville contient le maximum de clients ---------------------------
alter procedure ps_ville_de_client_max
	as
	begin 
		select top 1 with ties count(VilleClient) as number ,  VilleClient from CLIENT
         group by VilleClient	
		 order by number desc 
	end
	exec ps_ville_de_client_max
	go
------------------------------------ les factures d’un client donné --------------------------------
alter procedure ps_facture_client_donnee
	@IdClient as int
	as
	begin
	select * from FACTURE 
	where IdClient = @IdClient
end
 exec ps_facture_client_donnee 1
go
----------------------------- les clients qui n’ont jamais passé un commande -------------------------
alter procedure client_jamais_passe_commande
as
begin	
	select * from 
		CLIENT 
			where IdClient not in (select IdClient from FACTURE cross join LIGNECOMMANDE 
											where LIGNECOMMANDE.IdFacture = FACTURE.IdFacture)  
end
	exec client_jamais_passe_commande
go
---------------------------- la liste des produits commandés par un client donné ---------------------------
alter procedure ps_produits_client_donne
	@Idclient as int
as
begin
		select PRODUIT.IdProduit,IdCategorie,DesignationProduit,PrixUnitaireProduit,TvaProduit,Quantite from
		 FACTURE,LIGNECOMMANDE,PRODUIT 
		 where FACTURE.IdFacture = LIGNECOMMANDE.IdFacture and
				LIGNECOMMANDE.IdProduit = PRODUIT.IdProduit and 
				IdClient = @Idclient
end
	exec ps_produits_client_donne 1
go
-------------------------------------- le chiffre d’affaire par client ----------------------------------
------------------------------- pour tous les clients ----------------------------------
		alter view  view_chiffre_affaire_tous_clients
 as
	select
	 CLIENT.IdClient,
		ISNULL(SUM(PrixUnitaireProduit*Quantite*(TvaProduit+1)), 0) as CiffreAffaireClient
	from
 ((CLIENT
	left join FACTURE on CLIENT.IdClient = FACTURE.IdClient)
	left join LIGNECOMMANDE on FACTURE.IdFacture =LIGNECOMMANDE.IdFacture)
	left join PRODUIT on LIGNECOMMANDE.IdProduit = PRODUIT.IdProduit
	group by
	  CLIENT.IdClient
	select * from view_chiffre_affaire_tous_clients
	go
-------------------------------- pour un client donne -------------------------------------
alter procedure ps_chiffre_affaire_client_donne
	@Idclient as int 
	as 
	begin
		select * 
			 from view_chiffre_affaire_tous_clients
				 where
					IdClient = @IdClient  
	end 
	exec ps_chiffre_affaire_client_donne 3
	go
 ---------------------------- le chiffre d’affaire par produit d’un client donné -------------------------------
 alter procedure ps_ch_aff_produit_client_donne
	@IdClient as int
 as
 begin
	select
		LIGNECOMMANDE.IdProduit, sum(Quantite*PrixUnitaireProduit*(1+ TvaProduit)) as Ciff_aff_produit_client
		from
		 FACTURE, LIGNECOMMANDE, PRODUIT
		  where
			FACTURE.IdFacture = LIGNECOMMANDE.IdFacture and
			 LIGNECOMMANDE.IdProduit = PRODUIT.IdProduit and
			  IdClient = @IdClient
			group by
				LIGNECOMMANDE.IdProduit 
 end
  exec ps_ch_aff_produit_client_donne 2
	go

---------------------------- le chiffre d’affaire par une Categorie donnee ------------------------------
alter procedure ps_ch_aff_par_categorie
	@IdCategorie as int
 as
 begin
	select
		CATEGORIE.IdCategorie,NomCategorie, sum(Quantite*PrixUnitaireProduit*(1+ TvaProduit)) as Ciff_aff_par_categorie
		from
		LIGNECOMMANDE,PRODUIT,CATEGORIE
		where
			LIGNECOMMANDE.IdProduit = PRODUIT.IdProduit and
			 CATEGORIE.IdCategorie = @IdCategorie and 
			   PRODUIT.IdCategorie = @IdCategorie
			group by 
				CATEGORIE.IdCategorie,NomCategorie
 end
 exec ps_ch_aff_par_categorie 1
 go
 
 ---------------------------mettre à jour le chiffre d'affaire d'un client ---------------------
              ----------------------- par curseur ---------------------------------
 alter procedure ps_mettreAjour_chi_affi_client
 as
 begin
	declare
		@IdClient as int,
		@CiffreAffaireClient as float 
	declare curs_mettreAjour_Chiff cursor local
   for 
	select IdClient,CiffreAffaireClient  from view_chiffre_affaire_tous_clients
	open curs_mettreAjour_Chiff 
	fetch next from curs_mettreAjour_Chiff into @IdClient, @CiffreAffaireClient
	while(@@fetch_status = 0)
	begin
		update
			CLIENT
				set
				ChiffreAffaireClient = @CiffreAffaireClient
			where
			IdClient = @IdClient
		fetch next from curs_mettreAjour_Chiff into @IdClient, @CiffreAffaireClient
 end
close curs_mettreAjour_Chiff
 deallocate  curs_mettreAjour_Chiff
end
exec ps_mettreAjour_chi_affi_client 
select * from CLIENT
select * from view_ca_par_client
       ---------------------- par trigger --------------------------------
create trigger Chiffre_Affaire_trigger
 on LIGNECOMMANDE
	after UPDATE, INSERT, DELETE
 as
 declare
	@IdClient AS INT,
	@MontantCommande AS REAL
  if exists(SELECT * from inserted) and exists (SELECT * from deleted)
 begin
   DECLARE
		@IdClientAvant AS INT,
		@IdClientApres AS INT,
		@MontantCommandeAvant AS REAL,
		@MontantCommandeApres AS REAL
  SELECT
	@IdClientAvant = IdClient,
	@MontantCommandeAvant = Quantite*PrixUnitaireProduit*(1 + TvaProduit)
  FROM
		FACTURE, DELETED, PRODUIT
		WHERE
			FACTURE.IdFacture = DELETED.IdFacture and
			DELETED.IdProduit = PRODUIT.IdProduit
 
	SELECT
		@IdClientApres = IdClient,
		@MontantCommandeApres = Quantite*PrixUnitaireProduit*(1 + TvaProduit)
	FROM
		FACTURE, INSERTED, PRODUIT
		WHERE
		FACTURE.IdFacture = INSERTED.IdFacture AND
		INSERTED.IdProduit = PRODUIT.IdProduit 

   UPDATE
		CLIENT
		SET
			ChiffreAffaireClient = ChiffreAffaireClient - @MontantCommandeAvant
		WHERE
		IdClient = @IdClientApres
   UPDATE
		CLIENT
			SET
			ChiffreAffaireClient = ChiffreAffaireClient + @MontantCommandeApres
		WHERE
		IdClient = @IdClientApres
 end

 If exists (Select * from inserted) and not exists(Select * from deleted)
begin

	SELECT
	@IdClient = IdClient,
	@MontantCommande = Quantite*PrixUnitaireProduit*(1 + TvaProduit) 
	FROM
		FACTURE, INSERTED, PRODUIT
		WHERE
		FACTURE.IdFacture = INSERTED.IdFacture AND
		INSERTED.IdProduit = PRODUIT.IdProduit
    UPDATE
		 CLIENT
			SET
			ChiffreAffaireClient = ChiffreAffaireClient + @MontantCommande
		WHERE
		IdClient = @IdClient
end

 If exists(select * from deleted) and not exists(Select * from inserted)
begin 
	SELECT
	@IdClient = IdClient,
	@MontantCommande = Quantite*PrixUnitaireProduit*(1 + TvaProduit) 
	FROM
		FACTURE, DELETED, PRODUIT
		WHERE
		FACTURE.IdFacture = DELETED.IdFacture AND
		DELETED.IdProduit = PRODUIT.IdProduit
   UPDATE
	    CLIENT
			SET
			ChiffreAffaireClient = ChiffreAffaireClient - @MontantCommande
		WHERE
		IdClient = @IdClient

end
GO 
------------------------------ mettre à jour la quantite stockee d'un produit ------------------------
			--------------------- Quantite disponible pour chaque produit -------------------
create view view_Qn_FOURNIR_Totale_par_produit
as 
SELECT        QuantiteStockee as QntDisponible
FROM            PRODUIT
	where PRODUIT.IdProduit=FOURNIR.IdProduit
	group by(FOURNIR.IdProduit)

select * from view_Qn_FOURNIR_Totale_par_produit
go
-----------------------------------------------------------
alter view view_Qn_stockee_par_produit
as 
SELECT        PRODUIT.IdProduit,QuantiteStockee as QntDisponible 
FROM            PRODUIT
 
go
select * from view_Qn_stockee_par_produit
go
----------------------- mettre a jour quantite stockee d'un produit apres une operation de fournir -------------------------
	alter  trigger qun_fournie_trigger
on FOURNIR
after UPDATE, INSERT, DELETE
as
declare
 @IdFournisseur as int ,
 @IdProduit AS INT,
 @QntFournie AS int
if exists(SELECT * from inserted) and exists (SELECT * from deleted)
begin
   DECLARE
 @IdPoduitAvant AS INT,
 @IdProduitApres AS INT,
 @QntFournieAvant AS int,
 @QntFournieApres AS int
 SELECT
 @IdPoduitAvant = FOURNIR.IdProduit,
 @QntFournieAvant = deleted.QntFournie,
 @IdFournisseur = FOURNIR.IdFournisseur
 FROM
 FOURNIR, DELETED, PRODUIT
 WHERE
 FOURNIR.IdProduit = DELETED.IdProduit AND
 FOURNIR.IdFournisseur = DELETED.IdFournisseur and
 DELETED.IdProduit = PRODUIT.IdProduit 

 
 SELECT
 @IdProduitApres =  FOURNIR.IdProduit ,
 @QntFournieApres = inserted.QntFournie,
 @IdFournisseur = FOURNIR.IdFournisseur
 from
 FOURNIR, INSERTED, PRODUIT
 WHERE
 FOURNIR.IdProduit = INSERTED.IdProduit AND
 FOURNIR.IdFournisseur = INSERTED.IdFournisseur and
 INSERTED.IdProduit = PRODUIT.IdProduit 

 UPDATE
 PRODUIT
 SET
 QuantiteStockee = QuantiteStockee - @QntFournieAvant
 WHERE
 PRODUIT.IdProduit = @IdProduitApres
 UPDATE
 PRODUIT
 SET
 QuantiteStockee =	QuantiteStockee + @QntFournieApres
 WHERE
 PRODUIT.IdProduit = @IdProduitApres

end

If exists (Select * from inserted) and not exists(Select * from deleted)
begin

 SELECT
 @IdProduit = FOURNIR.IdProduit,
 @QntFournie = FOURNIR.QntFournie 
 FROM
 FOURNIR, INSERTED, PRODUIT
 WHERE
 FOURNIR.IdProduit = INSERTED.IdProduit AND
 INSERTED.IdProduit = PRODUIT.IdProduit
 UPDATE
 PRODUIT
 SET
 QuantiteStockee = QuantiteStockee + @QntFournie
 WHERE
 IdProduit = @IdProduit
end

If exists(select * from deleted) and not exists(Select * from inserted)
begin 
 SELECT
 @IdProduit = FOURNIR.IdProduit,
 @QntFournie = FOURNIR.QntFournie
 FROM
 FOURNIR, DELETED, PRODUIT
 WHERE
 FOURNIR.IdProduit = DELETED.IdProduit AND
 DELETED.IdProduit = PRODUIT.IdProduit
 UPDATE
 PRODUIT
 SET
  QuantiteStockee = QuantiteStockee - @QntFournie
 WHERe
 IdProduit = @IdProduit
end
GO
----------------------- mettre a jour quantite stockee d'un produit apres une commande -------------------------
	alter  trigger qunCommandee_trigger
on LIGNECOMMANDE
after UPDATE, INSERT, DELETE
as
declare
 @IdProduit as int ,
 @IdFacture AS INT,
 @QuantiteCom AS int
if exists(SELECT * from inserted) and exists (SELECT * from deleted)
begin
   DECLARE
 @IdPoduitAvant AS INT,
 @IdProduitApres AS INT,
 @QuantiteComAvant AS int,
 @QuantiteComApres AS int
 SELECT
 @IdPoduitAvant = DELETED.IdProduit,
 @QuantiteComAvant = deleted.Quantite
 FROM
 FACTURE, DELETED, PRODUIT
 WHERE
 FACTURE.IdFacture = DELETED.IdFacture and
 DELETED.IdProduit = PRODUIT.IdProduit 
 SELECT
 @IdProduitApres =  inserted.IdProduit ,
 @QuantiteComApres = inserted.Quantite
 from
 FACTURE, INSERTED, PRODUIT
 WHERE
 FACTURE.IdFacture = INSERTED.IdFacture and
 INSERTED.IdProduit = PRODUIT.IdProduit 
 UPDATE
 PRODUIT
 SET
 QuantiteStockee = QuantiteStockee + @QuantiteComAvant
 WHERE
 PRODUIT.IdProduit = @IdProduitApres
 UPDATE
 PRODUIT
 SET
 QuantiteStockee =	QuantiteStockee - @QuantiteComApres
 WHERE
 PRODUIT.IdProduit = @IdProduitApres

end

If exists (Select * from inserted) and not exists(Select * from deleted)
begin

 SELECT
 @IdProduit = inserted.IdProduit,
 @QuantiteCom = inserted.Quantite
 FROM
 FACTURE, INSERTED, PRODUIT
 WHERE
 FACTURE.IdFacture=inserted.IdFacture and
 INSERTED.IdProduit = PRODUIT.IdProduit
 UPDATE
 PRODUIT
 SET
 QuantiteStockee = QuantiteStockee - @QuantiteCom --- on va soustrire la quantité de commande dans le stock
 WHERE
 IdProduit = @IdProduit
end

If exists(select * from deleted) and not exists(Select * from inserted)
begin 
 SELECT
 @IdProduit = deleted.IdProduit,
 @QuantiteCom = deleted.Quantite
 FROM
 FACTURE, DELETED, PRODUIT
 WHERE
 FACTURE.IdFacture=DELETED.IdFacture and
 DELETED.IdProduit = PRODUIT.IdProduit
 UPDATE
 PRODUIT
 SET
  QuantiteStockee = QuantiteStockee + @QuantiteCom --- on va rajouter la quantité de commande dans le stock
 WHERe
 IdProduit = @IdProduit
end
GO
--------------------------- mettre a jour l'etat(Disponibilité) d'un prouit lors de passage d'une commande ------------------
alter procedure ps_mettreAjour_Etat_Produit
 as
 begin
	declare
		@IdProduit as int,
		--@EtatProduit as int,
		@QntDisponible as int 
	declare curs_mettreAjour_Etat cursor local
   for 
	select IdProduit,QntDisponible from view_Qn_stockee_par_produit
	open curs_mettreAjour_Etat 
	fetch next from curs_mettreAjour_Etat into @IdProduit, @QntDisponible
	while(@@fetch_status = 0)
	begin
		update
			PRODUIT
				set
				EtatProduit = 0
			where
			IdProduit = @IdProduit and
			@QntDisponible = 0
		update
			PRODUIT
				set
				EtatProduit = 1
			where
			IdProduit = @IdProduit and
			@QntDisponible > 0

		fetch next from curs_mettreAjour_Etat into @IdProduit, @QntDisponible
 end
close curs_mettreAjour_Etat
 deallocate  curs_mettreAjour_Etat
end
go
---------------------------------------- procedure de passage d'une commande ------------------------------------
	alter procedure passe_commande
  @IdFacture as int ,
  @IdProduit as int ,
  @Quantite as int 
as
begin
 declare @Qnt as int,
	     @Etat as int

		 set @Qnt = (select QuantiteStockee from PRODUIT
					where IdProduit=@IdProduit)
		set @Etat = (select EtatProduit from PRODUIT
					where IdProduit=@IdProduit)
		if(@Etat= 1) 
			begin
				if(@Quantite<= @Qnt)
					begin
					insert into LIGNECOMMANDE(IdFacture,IdProduit,Quantite) values (@IdFacture,@IdProduit,@Quantite)
					print 'commande bien passee'
					end
				else
						 begin 

							print 'la quantite demmandee est superieur a la quantite diponible '
							print 'essayez avec une quantite plus inferieur '
							print 'MERCI'
						
						 end
	        END
		ELSE 
			begin 
					print 'produit indisponible veuillez essayer ulterieurement ' 
			end
			exec ps_mettreAjour_Etat_Produit
			   
end
go
--------------------------------------FIN---------------------------------------------
 
