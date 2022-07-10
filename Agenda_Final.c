#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define filename1 "Pessoas.txt"
#define filename2 "Telefones.txt"
#define filename3 "Emails.txt"


typedef struct{
    int ID_Pessoa;
	char nome[20];
}Pessoa;


typedef struct{
    int ID_Telefone;
    int ID_Pessoa;
	char tel[11];
}Telefone;


typedef struct{
    int ID_Email;
    int ID_Pessoa;
	char email[30];
}Email;



int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET);
    return sz;
}

void flush_in()
{
   int ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

int VerificaID_P(FILE *file){

Pessoa contato;
int max=0;

while(fscanf(file,"%d %[^\n]%*c\n", &contato.ID_Pessoa, contato.nome)!=EOF){
		if(contato.ID_Pessoa > max)
			max = contato.ID_Pessoa;
            
}
return max;
}

int VerificaID_T(FILE *file){

Telefone contato;
int max=0;

while(fscanf(file,"%d %d %[^\n]%*c\n", &contato.ID_Telefone, &contato.ID_Pessoa, contato.tel)!=EOF){
          if(contato.ID_Telefone > max)
			max = contato.ID_Telefone;  
}
return max;
}

int VerificaID_E(FILE *file){

Email contato;
int max=0;

while(fscanf(file,"%d %d %[^\n]%*c\n", &contato.ID_Email, &contato.ID_Pessoa, contato.email)!=EOF){
          if(contato.ID_Email > max)
			max = contato.ID_Email;  
}
return max;
}


void Inserir_contato(){
Pessoa contato;

void Inserir_telefone(int ID), Inserir_email(int ID);

FILE *file1;

file1 = fopen(filename1, "a+t");


    if(file1 == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
    }
    else
    {
        if(!fsize(file1))
            contato.ID_Pessoa = 1;
        else
            contato.ID_Pessoa = VerificaID_P(file1) + 1;
        printf("Insira o nome:\n");
        scanf("%s", contato.nome);
        flush_in();
        
       
        fprintf(file1, "%d %s\n", contato.ID_Pessoa, contato.nome);
        fflush(file1);

        Inserir_telefone(contato.ID_Pessoa);
        Inserir_email(contato.ID_Pessoa);
       

}
fclose(file1);

}

void Inserir_telefone(int ID_Pessoa){
Telefone x;
int i=1;
char c;
FILE *file2;

file2 = fopen(filename2, "a+t");

    if(file2 == NULL)
    {
        printf("Não foi possível abrir o arquivo %s\n", filename2);
    }
    else
    {
        if(!fsize(file2))
            x.ID_Telefone = 1;
        else
            x.ID_Telefone = VerificaID_T(file2) + 1;

		x.ID_Pessoa = ID_Pessoa;
		
        while(i){
        
        printf("Insira o telefone:\n");
        scanf("%s", x.tel);
        flush_in();
        fprintf(file2, "%d %d %s\n", x.ID_Telefone, x.ID_Pessoa, x.tel);
        fflush(file2);
        printf("Deseja inserir outro telefone? (S) Sim, (Qualquer tecla) Não\n");
        c=getchar();
        flush_in();
        if(c == 'S' || c == 's')
            x.ID_Telefone+=1;
        else
            i=0;
                   
}
        
}

fclose(file2);
	
}

void Inserir_email(int ID_Pessoa){
Email x;
int i=1;
char c;
FILE *file3;

file3 = fopen(filename3, "a+t");

    if(file3 == NULL)
    {
        printf("Não foi possível abrir o arquivo %s\n", filename3);
    }
    else
    {
        if(!fsize(file3))
            x.ID_Email = 1;
        else
            x.ID_Email = VerificaID_E(file3) + 1;

        
        x.ID_Pessoa = ID_Pessoa;

        while(i){
        
        printf("Insira o email:\n");
        scanf("%s", x.email);
        flush_in();
        fprintf(file3, "%d %d %s\n", x.ID_Email, x.ID_Pessoa, x.email);
        fflush(file3);
        printf("Deseja inserir outro email? (S) Sim, (Qualquer tecla) Não\n");
        c = getchar();
        flush_in();
        if(c=='S' || c == 's')
            x.ID_Email+=1;
        else
            i=0;
                   
}
        
}

fclose(file3);
	
}

void Inserir(){
int i, ID;


system("clear");
printf("|-----Escolha uma opção------|\n");
printf("|                            |\n");
printf("|--- 1 - Inserir contato ----|\n");
printf("|--- 2 - Inserir Telefone ---|\n");
printf("|--- 3 - Inserir Email ------|\n");
printf("|--- 4 ------- Voltar------- |\n");
printf("|----------------------------|\n");
printf("|============================|\n");

scanf("%d", &i);
switch (i) {
            case 1:
                Inserir_contato();
                break;
            case 2:
				printf("Insira o ID do contato.\n");
				scanf("%d", &ID);
				flush_in();
                Inserir_telefone(ID);
                break;
            case 3:
				printf("Insira o ID do contato.\n");
				scanf("%d", &ID);
				flush_in();
                Inserir_email(ID);
                break;
            case 4:
                break;
                
        }
system("clear");
}


void Abrir(){

Pessoa contato;
Telefone tel;
Email em;
char c;

FILE *file1, *file2, *file3;
file1 = fopen(filename1, "r+t");
file2 = fopen(filename2, "r+t");
file3 = fopen(filename3, "r+t");

    if(file1 == NULL || file2 == NULL || file3 == NULL)
    {
        printf("Não foi possível abrir um dos arquivos\n");
    }
    else
    {
		printf("Digite (T) para exibir todos os contatos ou o ID desejado:\n");
		scanf("%c",&c);
		flush_in();
		if(c =='T' || c == 't'){
			system("clear");
			printf("---------------------------------------AGENDA----------------------------------------\n");
			printf("======================================================================================\n");
			printf("||--ID--||------------Nome----------||----Telefone--||--------------Email-----------||\n");
			printf("--------------------------------------------------------------------------------------\n");
							
			while(fscanf(file1,"%d %[^\n]%*c\n", &contato.ID_Pessoa, contato.nome)!=EOF){
					printf(" %d  \t \t %s \n",contato.ID_Pessoa, contato.nome);
					while(fscanf(file2,"%d %d %[^\n]%*c\n", &tel.ID_Telefone, &tel.ID_Pessoa, tel.tel)!=EOF){
							if(tel.ID_Pessoa == contato.ID_Pessoa)
								printf(" \t \t \t \t \t %s \n",tel.tel);
}
							while(fscanf(file3,"%d %d %[^\n]%*c\n", &em.ID_Email, &em.ID_Pessoa, em.email)!=EOF){
									if(em.ID_Pessoa == contato.ID_Pessoa)
										printf(" \t \t \t \t \t \t \t \t %s \n",em.email);
}
						
file3 = fopen(filename3, "r+t");
file2 = fopen(filename2, "r+t");							
}
}
		else{
			system("clear");
			printf("---------------------------------------AGENDA----------------------------------------\n");
			printf("======================================================================================\n");
			printf("||--ID--||------------Nome----------||----Telefone--||--------------Email-----------||\n");
			printf("--------------------------------------------------------------------------------------\n");
							
			while(fscanf(file1,"%d %[^\n]%*c\n", &contato.ID_Pessoa, contato.nome)!=EOF){
					if(contato.ID_Pessoa == strtol(&c,NULL,10))
						printf(" %d  \t \t %s \n",contato.ID_Pessoa, contato.nome);
					while(fscanf(file2,"%d %d %[^\n]%*c\n", &tel.ID_Telefone, &tel.ID_Pessoa, tel.tel)!=EOF){
							if(tel.ID_Pessoa == strtol(&c,NULL,10))
								printf(" \t \t \t \t \t %s \n",tel.tel);
}
							while(fscanf(file3,"%d %d %[^\n]%*c\n", &em.ID_Email, &em.ID_Pessoa, em.email)!=EOF){
									if(em.ID_Pessoa == strtol(&c,NULL,10))
										printf(" \t \t \t \t \t \t \t \t %s \n",em.email);
}
						
file3 = fopen(filename3, "r+t");
file2 = fopen(filename2, "r+t");							
}

}
printf("\n\nPressione qualquer tecla para voltar ao menu principal\n");

getchar();

}

fclose(file1);
fclose(file2);	
fclose(file3);

}

void Editar(){
int i=0, j, k=1, l=0, ID, count=0, countE=0, countT=0;
char c, temp[100];

Pessoa contato, Arq_novo[100]={0}, Nome_novo[100];
Telefone x, Tel_edt[100]={0}, Tel_novo[100];
Email y, Em_edt[100]={0}, Em_novo[100];

FILE *file1, *file2, *file3;
file1 = fopen(filename1, "a+t");
file2 = fopen(filename2, "a+t");
file3 = fopen(filename3, "a+t");

    if(file1 == NULL || file2 == NULL || file3 == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
    }
    else
    {
        printf("Insira o ID do contato para editar.\n");
        scanf("%d", &ID);
        printf("Insira o nome, ou \"Esc\" para manter:\n");
        scanf("%s", temp);
        flush_in();
        if(temp[0] != 27)
			strcpy(Nome_novo[0].nome,temp);
	Nome_novo[0].ID_Pessoa = ID;


        while(k){
        
        printf("Insira o telefone, ou \"Esc\" para manter:\n");
        scanf("%s", temp);
        flush_in();
        if(temp[0] != 27)
			strcpy(Tel_edt[countT].tel,temp);
		else
			break;
        Tel_edt[countT].ID_Pessoa = ID;
        printf("Deseja inserir outro telefone? (S) Sim, (Qualquer tecla) Não\n");
        scanf("%c", &c);
        flush_in();
        if(c =='S' || c == 's')
            countT+=1;
        else{
            k=0;
            countT+=1;
         }
                   
}
				
        k=1;
        while(k){
        
        printf("Insira o email, ou \"Esc\" para manter:\n");
        scanf("%s", temp);
        flush_in();
        if(temp[0] != 27)
			strcpy(Em_edt[countE].email,temp);
		else
			break;
        Em_edt[countE].ID_Pessoa = ID;
        printf("Deseja inserir outro email? (S) Sim, (Qualquer tecla) Não\n");
        scanf("%c", &c);
        flush_in();
        if(c =='S' || c == 's')
            countE+=1;
        else{
            k=0;
            countE+=1;
		}
                   
}	
		i=0;
        while(fscanf(file1,"%d %[^\n]%*c\n", &contato.ID_Pessoa, contato.nome)!=EOF){
				if(contato.ID_Pessoa != ID){
				    Arq_novo[i].ID_Pessoa = contato.ID_Pessoa;
                    strcpy(Arq_novo[i].nome,contato.nome);
                    i++;}
					
}


fclose(file1);

file1 = fopen(filename1, "w+t");

for(j=0;j<i+1;j++){
	if(j == i){
		fprintf(file1, "%d %s\n",Nome_novo[0].ID_Pessoa, Nome_novo[0].nome);
		fflush(file1);
	}
	else{	
    fprintf(file1, "%d %s\n",Arq_novo[j].ID_Pessoa, Arq_novo[j].nome);
    fflush(file1);
}
}

		k=0;
		
			while(fscanf(file2,"%d %d %[^\n]%*c\n", &x.ID_Telefone, &x.ID_Pessoa, x.tel)!=EOF){
                if (x.ID_Pessoa != ID){
					Tel_novo[k].ID_Pessoa = x.ID_Pessoa;
                    strcpy(Tel_novo[k].tel,x.tel);
                    k++;
                  }
                 if (x.ID_Pessoa == ID && Tel_edt[0].tel == 0){
					Tel_novo[k].ID_Pessoa = x.ID_Pessoa;
                    strcpy(Tel_novo[k].tel,x.tel);
                    k++;
                  }     
}
		fclose(file2);
		file2 = fopen(filename2, "w+t");

		for(j=0;j<k+1;j++){
			if(j == k){
				for(i=0; i<countT; i++){
					fprintf(file2, "%d %d %s\n",count+1, Tel_edt[i].ID_Pessoa, Tel_edt[i].tel);
					fflush(file2); 
					count+=1;
		}
	}
			else{
			fprintf(file2, "%d %d %s\n",count+1, Tel_novo[j].ID_Pessoa, Tel_novo[j].tel);
			fflush(file2);
			count+=1; 
}
}

		
			while(fscanf(file3,"%d %d %[^\n]%*c\n", &y.ID_Email, &y.ID_Pessoa, y.email)!=EOF){
                if (y.ID_Pessoa != ID){
					Em_novo[l].ID_Pessoa = y.ID_Pessoa;
                    strcpy(Em_novo[l].email,y.email);
                    l++;
                  }
                 if (y.ID_Pessoa == ID && Em_edt[0].email == 0){
					Em_novo[l].ID_Pessoa = y.ID_Pessoa;
                    strcpy(Em_novo[l].email,y.email);
                    l++;
                  }     
}
		fclose(file3);
		file3 = fopen(filename3, "w+t");
		count= 0;
		for(j=0;j<l+1;j++){
			if(j == l){
				for(i=0; i<countE; i++){
				fprintf(file3, "%d %d %s\n",count+1, Em_edt[i].ID_Pessoa, Em_edt[i].email);
				fflush(file3); 
				count+=1;
			}
		}
			else{
			fprintf(file3, "%d %d %s\n",count+1, Em_novo[j].ID_Pessoa, Em_novo[j].email);
			fflush(file3);
			count+=1; 
}

}


fclose(file1);
fclose(file2);
fclose(file3);
}
}


void Excluir(){
int i=0, k = 0, l = 0, j, ID;

Pessoa contato, Arq_novo[100];
Telefone x, Tel_novo[100];
Email y, Em_novo[100];

FILE *file1, *file2, *file3;
file1 = fopen(filename1, "r+t");
file2 = fopen(filename2, "r+t");
file3 = fopen(filename3, "r+t");

    if(file1 == NULL || file2 == NULL || file3 == NULL)
    {
        printf("Não foi possível abrir um dos arquivos\n");
    }
    else
    {
        printf("Insira o ID a ser excluido da agenda.\n");
        scanf("%d", &ID);
        flush_in();

      
        while(fscanf(file1,"%d %[^\n]%*c\n", &contato.ID_Pessoa, contato.nome)!=EOF){
                if (contato.ID_Pessoa < ID){
                    Arq_novo[i].ID_Pessoa = contato.ID_Pessoa;
                    strcpy(Arq_novo[i].nome,contato.nome);
                    i++;
}
				if (contato.ID_Pessoa > ID){
                    Arq_novo[i].ID_Pessoa = contato.ID_Pessoa-1;
                    strcpy(Arq_novo[i].nome,contato.nome);
                    i++;
}
}
		
		while(fscanf(file2,"%d %d %[^\n]%*c\n", &x.ID_Telefone, &x.ID_Pessoa, x.tel)!=EOF){
                if (x.ID_Pessoa < ID){
					Tel_novo[k].ID_Telefone = x.ID_Telefone;
                    Tel_novo[k].ID_Pessoa = x.ID_Pessoa;
                    strcpy(Tel_novo[k].tel,x.tel);
                    k++;
                  }
                if (x.ID_Pessoa > ID){
					Tel_novo[k].ID_Telefone = x.ID_Telefone;
                    Tel_novo[k].ID_Pessoa = x.ID_Pessoa-1;
                    strcpy(Tel_novo[k].tel,x.tel);
                    k++;
                  }   
}
		
		while(fscanf(file3,"%d %d %[^\n]%*c\n", &y.ID_Email, &y.ID_Pessoa, y.email)!=EOF){
                if (y.ID_Pessoa < ID){
					Em_novo[l].ID_Email = y.ID_Email;
                    Em_novo[l].ID_Pessoa = y.ID_Pessoa;
                    strcpy(Em_novo[l].email,y.email);
                    l++;
                  }
                if (y.ID_Pessoa > ID){
					Em_novo[l].ID_Email = y.ID_Email;
                    Em_novo[l].ID_Pessoa = y.ID_Pessoa-1;
                    strcpy(Em_novo[l].email,y.email);
                    l++;
                  }
}


fclose(file1);
fclose(file2);
fclose(file3);

file1 = fopen(filename1, "w+t");
file2 = fopen(filename2, "w+t");
file3 = fopen(filename3, "w+t");

for(j=0;j<i;j++){
    fprintf(file1, "%d %s\n",Arq_novo[j].ID_Pessoa, Arq_novo[j].nome);
    fflush(file1); 
}

for(j=0;j<k;j++){
    fprintf(file2, "%d %d %s\n",Tel_novo[j].ID_Telefone, Tel_novo[j].ID_Pessoa, Tel_novo[j].tel);
    fflush(file2); 
}

for(j=0;j<l;j++){
    fprintf(file3, "%d %d %s\n",Em_novo[j].ID_Email, Em_novo[j].ID_Pessoa, Em_novo[j].email);
    fflush(file3); 
}

}

fclose(file1);
fclose(file2);
fclose(file3);
}


int main(void){

int escolha;


while(1){

    
printf("|-----------AGENDA-----------|\n");
printf("|                            |\n");
printf("|-----Escolha uma opção------|\n");
printf("|                            |\n");
printf("|--- 1 - Inserir registro ---|\n");
printf("|--- 2 - Editar registro  ---|\n");
printf("|-- 3 - Excluir registro ----|\n");
printf("|--- 4 - Visualizar registro |\n");
printf("|--- 5 - ------Sair----------|\n");
printf("|                            |\n");
printf("|----------------------------|\n");
printf("|============================|\n");


		
scanf("%d", &escolha);
flush_in();

switch (escolha) {
            case 1:
                Inserir();
                break;
            case 2:
                Editar();
                break;
            case 3:
                Excluir();
                break;
            case 4:
                Abrir();
                break;
            case 5:
                exit(0);
                
        }

system("clear");

}
system("exit");
return (EXIT_SUCCESS);
}


