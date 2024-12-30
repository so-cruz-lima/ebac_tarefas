
#include <stdio.h>//biblioteca de comunicacao com o usuario
#include <stdlib.h>//biblioteca de alocacao de espaco em memoria
#include <locale.h>//biblioteca de alocacoes de texto por regiaAO
#include <string.h>// bibiloteca de manipulacao de textos / Strings

const int MAC = 1;
const int WIN = 2;

/**
 Define qual o sistema operacional será utilizado.
 Temporariamente as atribuicoes sao manuais.

 Posteriormente será modificado por atribuicao direto por
validacao das macros "TARGET_OS_MAC" , "__APPLE__" ,  "_WIN32", "_WIN64"
 */
const int OS = WIN;

const char FILE_MODE_WRITE  [1]   = "w";
const char FILE_MODE_APPEND [1]   = "a";
/**
 Esta constante define manualmente onde os arquivos serao salvos
 no MAC_OS
 */
const char FILE_PATH_MAC    [50]  = "/Users/me/Documents/EBAC/cartorio";

/**
 Esta funcao cria um envelope para validar se o sistema operacional salvo na constante OS é igual ao VALOR da constante MAC.
 Caso sim , ela criara um efeito semelhante ao pause e aguardará o input do usuario para prosseguir.
 No caso do valor de OS ser igual a WIN, a funcao PAUSE do sistema operacional será chamada.
 
 Esta funcao foi criada para solucionar temporairamente o problema da restricao de acesso aos comandos do Sistema por meio do Terminal do MACOS
 */
void system_pause(void){
    if(OS == MAC){
        int pauseVal;
        printf("Entre com um valor numerico e pressione enter \n");
        scanf("%d", &pauseVal);
    } else {
        system("pause");
    }

}

/**
 Esta funcao cria um envelope para validar se o sistema operacional salvo na constante OS é igual ao VALOR da constante MAC.
 Caso sim , ela criara um efeito de limpeza de tela semelhante ao CLS, inserindo 80 linhas em branco.
 No caso do valor de OS ser igual a WIN, a funcao CLS do sistema operacional será chamada.
 
 Esta funcao foi criada para solucionar temporairamente o problema da restricao de acesso aos comandos do Sistema por meio do Terminal do MACOS
 */
void system_cls(void){
    if(OS == MAC){
        int linha=0;
        for(linha=0;linha<80;linha++){
            printf("\n");
        }
    }else{
        system("cls");
    }
}


/**
  Esta funcao escreve um texto / string em um arquivo.
  Esta funcao foi criada para evitar facilitar a leitura da funcao cadastra e evitar a repeticao de código.
  
 Parametros :
    char* strFileName - parametro que indica o nome do arquivo
    char *strContent   - parametro que contem o texto com o conteudo que será escrito / salvo no arquivo
    char fileMode []     - Determina o tipo de abertura do arquivo . Existem 2 modos definidos pelas seguintes constantes :
    a) FILE_MODE_WRITE equivale a string  "w", onde o arquivo sera criado e o abre o arquivo para escrita apartir do byte 0
    b) FILE_MODE_APPEND equivale a string  "a" e abre o aqruivo ja criado, colocando a escrita no arquivo no ultimo byte valido.
*/
void arquivoEscrever(char* strFileName, char *strContent, char fileMode []){
    FILE *file;
    file = fopen(strFileName,  fileMode );
    fprintf(file, strContent);
    fclose(file);
}


/**
 Esta funcao cadastra uma pessoa.
 O usuario deve inserir um cpf.
 Este CPF será utilizado como nome do arquivo.
 
 Caso o valor de OS seja MAC, entao será adionado o caminho válido ao nome do arquivo.
 O arquivo será criado ou recriado, caso exista.
 Para cada informacao ( NOME, SOBRENOME, CARGO) , será pedido que o usuairo digite-a.
 Cada informacao inserida, será salva no aquivo.
 Ao fim, o fluxo do sistema retornará ao menu principal
*/
void registro(void){
    
    setlocale (LC_ALL, "Portuguese");
    
    // caso opcao seja 1 | exibe a tela de cadastro de nomes
    /**
      Os comandos char **** [40]; criam arrays do tipo char com 40 posicoes / caracteres.
      Isto equivale a uma string ou texto de no maximo 40 letras
     */
    char pessoaCpf           [40];
    char pessoaNome          [40];
    char pessoaSobrenome     [40];
    char pessoaCargo         [40];
    
    /**
     cria um array do tipo char com 200 posicoes / caracteres
     Isto equivale a uma string ou texto de no maximo 200 letras
     */
    char arquivoNome         [200];
    
    
    printf("-------------------------- \n");
    printf("Cadastro \n");
    printf("-------------------------- \n");
    
    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s",pessoaCpf);
    // caso o Sistema operacional esteja marcado como MAC
    if(OS == MAC ){
        // copia o caminho valido, representado pela constante FILE_PATH_MAC, para o nome do aquivo
        strcpy(arquivoNome, FILE_PATH_MAC);
        strcat(arquivoNome, pessoaCpf);
    } else {
        strcpy(arquivoNome, pessoaCpf); // existem 2 valores possiveis :
        // 1o - com o windows nao existira o caminho adicionado antes do valor do CPF na variavel nomeDoArquivo
        // 2o - com o mac , para que o arquivo seja encontrado, o caminho da pasta /Users/socorro/Documents/EBAC/Programação C/ sera adicionado em frente ao numero do cpf.
    }
    arquivoEscrever(arquivoNome, pessoaCpf , FILE_MODE_WRITE);
    arquivoEscrever(arquivoNome, "," , FILE_MODE_APPEND);
        
    printf("Digite o Nome a ser cadastrado: ");
    scanf("%s",pessoaNome);
    arquivoEscrever(arquivoNome, pessoaNome , FILE_MODE_APPEND);
    arquivoEscrever(arquivoNome, "," , FILE_MODE_APPEND);
    
     printf("Digite o Sobrenome a ser cadastrado: ");
     scanf("%s",pessoaSobrenome);
     arquivoEscrever(arquivoNome, pessoaSobrenome , FILE_MODE_APPEND);
     arquivoEscrever(arquivoNome, "," , FILE_MODE_APPEND);
    
     printf("Digite o Cargo a ser cadastrado: ");
     scanf("%s",pessoaCargo);
     arquivoEscrever(arquivoNome, pessoaCargo , FILE_MODE_APPEND);
    
    system_pause(); // chamada de pause duplicado. poderia ser colocado fora do switch case
} // finaliza a execucao da funcao cadastrar e retorna para a funcao main, na linha 206

/**
 Esta funcao aguarda a entrada de um cpf e aber o arquivo com o nome igual ao cpf digitado.
 caso o arquivo nao exista, uma mensagem de erro sera exibida e o fluxo retornara ao menu principal.
*/
void consulta(void){
    
    setlocale (LC_ALL, "Portuguese");
    
    char pessoaCpf           [40];
    char arquivoNome         [200];
    char arquivoConteudo     [200];
    
    
    printf("-------------------------- \n");
    printf("Consulta \n");
    printf("-------------------------- \n");
    
    printf("Digite o CPF a ser consultado: ");
    scanf("%s",pessoaCpf);
    // caso o Sistema operacional esteja marcado como MAC
    if(OS == MAC ){
        // copia o caminho valido, representado pela constante FILE_PATH_MAC, para o nome do aquivo
        strcpy(arquivoNome, FILE_PATH_MAC);
        strcat(arquivoNome, pessoaCpf);
    } else {
        strcpy(arquivoNome, pessoaCpf); // existem 2 valores possiveis :
        // 1o - com o windows nao existira o caminho adicionado antes do valor do CPF na variavel nomeDoArquivo
        // 2o - com o mac , para que o arquivo seja encontrado, o caminho da pasta /Users/socorro/Documents/EBAC/Programação C/ sera adicionado em frente ao numero do cpf.
    }
    
    FILE *file;
    file = fopen(arquivoNome,  "r" ); // w - escreve o arquivo do zero. E se o arquivo existir, ele apaga o conteudo
    // a
    // r
    
    if(file == NULL){
        printf("Nao foi possivel abrir o arquivo , nao localizado! \n");
    } else {
        //fread( arquivoConteudo, sizeof(char), 200, file); // le o arquivo com um buffer arquivoConteudo do tamanho 200 * 8 -> sizeof(char)
        
        while(fgets(arquivoConteudo, 200, file) != NULL){// le o arquivo 200 vezes, caracter por caracter, ou ate ler o ultimo byte valido, que nao seja nulo
            printf("\n Essa sao as informacoes do usuário : ");
            printf(" %s ",arquivoConteudo);
            printf("\n\n");
        }
        
        printf(" Dados da pessoa cadastrada com CPF %s \n",pessoaCpf);
        printf(" %s \n",arquivoConteudo);
        printf(" ------------------------- \n");
    }
    
    fclose(file);
    system_pause();
} // finaliza a chamada da funcao consultar e retorna para a funcao main, na linha 211

/**
  Remove o arquivo de um usuario registrado.
 O nome do aquivo equivale ao cpf do usuario.
  
*/
void remover(void){
   
    char pessoaCpf           [40];
    char arquivoNome         [200];
    
    
    printf("-------------------------- \n");
    printf("Remover \n");
    printf("-------------------------- \n");
    
    printf("Digite o CPF do usuario a ser removido: ");
    scanf("%s",pessoaCpf);
   
    if(OS == MAC ){
    
        strcpy(arquivoNome, FILE_PATH_MAC);
        strcat(arquivoNome, pessoaCpf);
    } else {
        strcpy(arquivoNome, pessoaCpf);
    }
    
    FILE *file;
    file = fopen(arquivoNome,  "r" );

    // verifica se o arquivo existe
    if(file != NULL){
        fclose(arquivoNome);
        
        int deletar = 0;
        printf("Voce realmente deseja deletar o arquivo %s ? ", arquivoNome);
        printf("\n 1 - Sim / 2 - Nao ");
        scanf("%d", &deletar);
        
        // remove o arquivo selecionado
        if(deletar == 1) {
            remove(arquivoNome);
            
            file = fopen(arquivoNome,  "r" );
            
            if(file == NULL){
                printf("O arquivo foi removido com sucesso ");
            }
        }
    } else {
        // informa que o arquivo nao existe
        printf("O arquivo %s nao existe ", arquivoNome);
    }
    
    system_pause(); // chamada de pause duplicado. poderia ser colocado fora do switch case
} // retorne para linha 68

/*
 ponto de entrada para programas em C e C++
 Este metodo exibe o menu principal.
 */
int main(void)
{
    // cria a variavel opcao, que salvará a ultima opcao selecionada no menu principal
    // a váriavel é do tipo inteiro e é inicializada com o valor 0
    int opcao=0;
    int laco=1;
    
    for(laco=1;laco==1;){
        system_cls();
        setlocale (LC_ALL, "Portuguese");
        
        // exibe o menu principal
        printf("### Cartório da EBAC ###\n\n");
        printf("Escolha a opção desejada do menu:\n\n");
        printf("\t1 - Registrar nomes\n");
        printf("\t2 - Consultar nome\n");
        printf("\t3 - Deletar nomes\n");
        printf("\t4 - Sair do programa\n");
        printf("Digite a opçāo:");
        
        scanf("%d", &opcao);// lê a entrada do teclado e salva o valor em opcao
        
        system_cls(); // limpa a tela
        
        
        switch(opcao) {
            case 1 : {
                registro(); // chama a funcao cadastrar, na linha 74
                break;
            } //case 1
            case 2 : {
                consulta(); // chama a funcao cadastrar, na linha 125
                break;
            } // case 2
            case 3 : {
                remover(); // vá para a linha 17
                break;
            }// case 3
            case 4 : {
                // sai do programa
                laco = 0;
                printf("Obrigado por usar o cartorío EBAC\n");
                
                /* adicionando um pause para dar tempo do outputstream ser
                 corretamente exibido. A interrupcao causada pelo return 0
                 interrompe a chamada do printf antes de sua finalizacao / flush.
                 Talvez este erro seja dependente do Sistema Operacional ?
                */
                
                system_pause();
                return 0;
                /* este break é desnecessario e nunca será chamado.
                 A chamada do return 0 já interrompe a execucao do fluxo da funcao MAIN e retira
                 a chamada desta funcao da pilha
                 */
                break;
                
            } // case 4
            default:{
                printf("Esta opção não está disponivel \n"); // exibe a tela de opcao invalida
                system_pause();
                /* break no ultimo case ou no default é inutil.
                  Nao há nenhum case posterior para que o brake interrompa a execucao do switch-case
                 */
                break;
            } // default
                
        }// swtich
        system_cls();
    } // quando esta linha for lida, retorna para a linha 31 do for
   
  return 1;
   
}
