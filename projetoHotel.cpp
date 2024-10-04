/*
EFMW - atividade 04
Murilo Carvalho Giroto

*/
#include <stdio.h>
int QuantPessoas = 0;
int QuantReserva = 0;
//Struct para definir o tipo de endereco, pessoa e apartamentos
typedef struct pEnde{
	char rua[255];
	int num;
	int cep;
} pende;
typedef struct pPessoa{
	char nome[255];
	int cpf;
	pende endereco; //uma pessoa tem um endereco
} ppessoa;
typedef struct pHotel{
	ppessoa hosp; // um apartamento pode ter uma pessoa
	char OcupReserv = '.'; //ocupado O reservado R vazio .
	
} Hotel;
//buffer
void fclear(){
	char carac;
	while((carac = fgetc(stdin)) != EOF && carac != '\n'){
	}
}
//===============================================================================================================
//procedimento para mostrar ao usuario a matriz do hotel (andar e apartamentos)
void PlanilhaHospedes(struct pHotel dados[][14]){
	printf("      ");
	for(int j = 0; j < 14; j++){
		printf("%.2d ", j+1);
	}
	printf("\n");
	
	for(int i = 19; i >= 0; i--){
		printf("[%.2d] ", i+1);
		for(int j = 0; j < 14; j++){
			//printf(dados[i][j].OcupReserv == '.' ? "%c" : "%c", dados[i][j].OcupReserv);
			printf(" %c ", dados[i][j].OcupReserv);
		}
		printf("\n");
	}
}
//===============================================================================================================
//pede ao usuario digitar um andar e apartamento, procedimento valida valores digitados pelo usuario
void VerfyAndar(Hotel dados[][14], int *ande, int *ap){
	printf("Escolha um andar e um apartamento (numero do andar e numero do apartamento exemp: 04 12)\n");
	PlanilhaHospedes(dados);
	printf("\n");
	int andar, apt;
	while(1){
		scanf("%d %d", &andar, &apt);
		if((andar >= 1 && andar <= 20) && (apt >= 1 && apt <= 14 )){
			break;
			/*if(dados[andar-1][apt-1].OcupReserv == 'O' || dados[andar-1][apt-1].OcupReserv == 'R')
				printf("Apartamento ja ocupado/reservado!\nSelecione outro\n");
			else
				break;	*/
		}
		printf("\nDigite um andar e apartamento corretamente!!!\n>> ");
	}
	andar--;
	apt--;
	*ande = andar;
	*ap = apt;
}
//===============================================================================================================
//primitiva para retornar o estado de um apartamento
char reservadoOcupado(Hotel dados){
	return dados.OcupReserv;
}
//===============================================================================================================
//caso usuario selecione a opcao de Dados de hospedes, ira mostrar os dados salvos do hospedes de um determinado apartamento
//ou seja, usuario digita um andar e apartamento e a funcao mostra os dados do hospede caso o apartamento digitado esteja reservado/ocupado
void HospedeUm(Hotel dados[][14]){
	int andar = 0, apto = 0;
	VerfyAndar(dados, &andar, &apto);
	
	if(reservadoOcupado(dados[andar][apto]) == 'O'){
		printf("Hospede: [%s]\n", dados[andar][apto].hosp.nome);
		printf("[Cpf] %d\n[Rua] %s\n[Numero] %d\n[CEP] %d\n", dados[andar][apto].hosp.cpf, dados[andar][apto].hosp.endereco.rua, dados[andar][apto].hosp.endereco.num, dados[andar][apto].hosp.endereco.cep);
		printf("Apartamento OCUPADO!\n");
	}else if(reservadoOcupado(dados[andar][apto]) == 'R'){
		printf("Hospede: [%s]\n", dados[andar][apto].hosp.nome);
		printf("[Cpf] %d\n", dados[andar][apto].hosp.cpf);
		printf("Apartamento RESERVADO!\n");
	}else
		printf("Apartamento VAZIO!\n");
	
	printf("Andar: [%d]  Apartamento: [%d]\n\n", andar+1, apto+1);
	printf("======================================\n");
}
//===============================================================================================================
//procedimento para cadastrar uma reserva a um usuario
void CadastraReserva(Hotel dados[][14]){
	int andar = 0, apt = 0;
	while(1){
		VerfyAndar(dados, &andar, &apt);
		if(dados[andar][apt].OcupReserv == '.')
			break;
		printf("=========================================\n");
		printf("====[ESCOLHA UM APARTAMENTO VAZIO!!!]====\n");
		printf("=========================================\n\n");
	}
	
	
	fclear();
	printf("Digite seu nome:\n>> ");
	gets(dados[andar][apt].hosp.nome);
	//scanf("%s", &dados[andar][apt].nome);
	fclear();
	
	printf("Digite seu cpf (sem pontos ou tracos exemp: 12345678910)\n>>");
	scanf("%d", &dados[andar][apt].hosp.cpf);
	fclear();
	dados[andar][apt].OcupReserv = 'R';
	QuantReserva++;
	printf("=======================================\n");
	printf("========[RESERVADO COM SUCESSO]========\n");
	printf("=======================================\n\n");
}
//===============================================================================================================
//funcao para cadastrar um usuario para ocupar um apartamento (caso esteja reservado, ira ocupa-lo)
int CadastroHospede(Hotel dados[][14]){
	int andar = 0, apt = 0;
	while(1){
		VerfyAndar(dados, &andar, &apt);
		if(dados[andar][apt].OcupReserv == '.')
			break;
		if(dados[andar][apt].OcupReserv == 'R'){
			int d = 0;
			printf("Voce havia reservado este apartamento? [1]- SIM  [2]- NAO\n>> ");
			scanf("%d", &d);
			if(d == 1){
				printf("Digite seu cpf cadastrado para efetuar o check-in:\n>> ");
				int cpf;
				scanf("%d", &cpf);
				if(dados[andar][apt].hosp.cpf == cpf){				
					printf("Bem vindo(a), [%s]\n\n", dados[andar][apt].hosp.nome);
					QuantReserva--;
					break;	
				}
			}
		}
		printf("===================================\n");
		printf("==[ESCOLHA UM APARTAMENTO VAZIO!]==\n");
		printf("===================================\n\n");
	}
	
	char Nome[255];
	
	if(dados[andar][apt].OcupReserv == '.'){
		fclear();
		printf("Digite seu nome:\n>> ");
		gets(dados[andar][apt].hosp.nome);
		fclear();
		//dados[andar][apt].hosp.cpf = cpf;
		printf("Digite seu cpf (sem pontos ou tracos exemp: 12345678910)\n>>");
		scanf("%d", &dados[andar][apt].hosp.cpf);
	}
	fclear();
	printf("Digite o nome de sua rua\n>>");
	gets(dados[andar][apt].hosp.endereco.rua);
	printf("Digite o numero da casa/apto\n>>");
	scanf("%d", &dados[andar][apt].hosp.endereco.num);
	printf("Digite o cep (sem pontos ou tracos)\n>>");
	scanf("%d", &dados[andar][apt].hosp.endereco.cep);
	
	dados[andar][apt].OcupReserv = 'O';
	QuantPessoas++;    // Adicionando o hospede em uma variavel
	printf("========================================\n");
	printf("======[CHECK-IN FEITO COM SUCESSO]======\n");
	printf("========================================\n\n");
	return 0;
}
//===============================================================================================================
//procedimento para remover hospede de um apartamento Ocupado ou Reservado
void RemoverCadastro(struct pHotel dados[][14], int ReservOcup){
	int andar = 0, apt = 0;
	VerfyAndar(dados, &andar, &apt);
	int cpf;
	if((dados[andar][apt].OcupReserv == 'R' && ReservOcup == 1)  || (dados[andar][apt].OcupReserv == 'O' && ReservOcup == 0)){
		printf("Confirme seu cpf cadastrado sem pontos ou tracos:\n>>");
		scanf("%d", &cpf);
		
		if(dados[andar][apt].hosp.cpf == cpf){
			if(dados[andar][apt].OcupReserv = 'O')
				QuantPessoas--;
			else
				QuantReserva--;
			dados[andar][apt].OcupReserv = '.';
			
			dados[andar][apt].hosp.cpf = 0;
			printf("===========================================\n");
			printf(ReservOcup? "======[RESERVA CANCELADA COM SUCESSO]======\n" : "=====[CHECK-OUT REALIZADO COM SUCESSO]=====\n");
			printf("===========================================\n\n");
		}else{
			printf("=========================================\n");
			printf("============[CPF INVALIDO!!!]============\n");
			printf("=========================================\n\n");
		}
	}else{
		printf("=====================================================\n");
		printf("======[APARTAMENTO VAZIO / REMOCAO INVALIDA!!!]======\n");
		printf("=====================================================\n\n");
	}
}

//===============================================================================================================
void opcoes(){
	printf("Selecione uma das opcoes abaixo:\n\n");
	printf("[1] Cadastro de hospede (Check-in)\n");
	printf("[2] Remover hospede (Check-out)\n");
	printf("[3] Reservar apartamento\n");
	printf("[4] Cancelar reserva\n");
	printf("[5] Planilha de hospedes\n");
	printf("[6] Dados de hospede (somente um hospede)\n");
	printf("[7] Taxas de ocupacao e reserva\n");
	printf("[8] Sair do programa\n\n>> ");
}
void taxaOcup(){
	
	float taxa = ((float)QuantPessoas/2.8);
	float taxaR = ((float) QuantReserva/2.8);
//	printf("Taxa: %f \n\n", (QuantPessoas/280) * 100); // 2,8
	printf("Taxa de Ocupacao: [%.2f%%]\nTaxa de Reserva: [%.2f%%]\n",taxa, taxaR);
	printf("======================================\n\n");
}	
//===============================================================================================================
main(){
	Hotel Hospedes[20][14];

	printf("======================================\n");
	printf("==========[Reserva de Hotel]==========\n");
	printf("======================================\n\n");	
	while(1){
		int op;
		opcoes();
		do{
			scanf("%d", &op);
			printf(op < 1 || op > 8 ? "\nOpcao invalida!!! Selecione corretamente\n>> " : "\n");
		}while(op < 1 || op > 8);
		
		if(op == 8)
			break;
		
		switch(op){
			case 1:
				CadastroHospede(Hospedes);
				break;
			case 2:
				RemoverCadastro(Hospedes, 0);
				break;
			case 3:
				CadastraReserva(Hospedes);
				break;
			case 4:
				RemoverCadastro(Hospedes, 1);
				break;
			case 5:
				PlanilhaHospedes(Hospedes);
				break;
			case 6:				
				HospedeUm(Hospedes);
				break;
			case 7:
				taxaOcup();
				break;
		}	
	}
}
