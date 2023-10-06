/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.richard.estrutura.dados;

/**
 *
 * @author 32216450
 */
public class Atividade2ArvoreBinaria {
    public void exemplo1() {
        Arvore<Integer> arvore = Arvore.<Integer>inicializa();
        
        // Insere os dados na arvore
        arvore.inserir(150, null);
        arvore.inserir(100, null);
        arvore.inserir(50, null);
        arvore.inserir(120, null);
        arvore.inserir(130, null);
        arvore.inserir(250, null);
        arvore.inserir(220, null);
        arvore.inserir(300, null);
        
        // Imprimi os dados da arvore
        arvore.emOrdem();
        arvore.preOrdem();
        arvore.posOrdem();
        
        // Pesquisa um no na arvore
        Integer no = arvore.pesquisaArvore(10);
        if (no != null) {
            System.out.println("Achou 10");
        } else {
            System.out.println("Não achou 10");
        }
        
        no = arvore.pesquisaArvore(130);
        if (no != null) {
            System.out.println("Achou 130");
        } else {
            System.out.println("Não achou 130");
        }
        
        System.out.println("Tamanho da arvore: " + arvore.length());
        System.out.println("Menor ra da arvore rec: " + arvore.menor());
        System.out.println("Maior ra da arvore rec: " + arvore.maior());
        
        System.out.println("Menor ra da arvore nrec: " + arvore.menor());
        System.out.println("Maior ra da arvore nrec: " + arvore.maior());
    }
    
    void exemplo2() {
        Arvore<Aluno> arvore = Arvore.<Aluno>inicializa();
        arvore.inserir(150, new Aluno(150, "Richard"));
        arvore.inserir(100, new Aluno(100, "Lucas"));
        arvore.inserir(50, new Aluno(50, "Alexandre"));
        arvore.inserir(120, new Aluno(120, "Ana Clara"));
        arvore.inserir(130, new Aluno(130, "Galadriel"));
        arvore.inserir(250, new Aluno(250, "Azazel"));
        
        // Imprimi os dados da arvore
        arvore.emOrdem();
        arvore.preOrdem();
        arvore.posOrdem();
        
        // Pesquisa alunos pelo ra
        Aluno aluno = arvore.pesquisaArvore(10);
        if (aluno != null) {
            System.out.println("Achou " + aluno);
        } else {
            System.out.println("Não Achou ");
        }
        
        aluno = arvore.pesquisaArvore(50);
        if (aluno != null) {
            System.out.println("Achou " + aluno);
        } else {
            System.out.println("Não Achou ");
        }
        
        System.out.println("Tamanho da arvore: " + arvore.length());
        System.out.println("Menor ra da arvore rec: " + arvore.menor());
        System.out.println("Maior ra da arvore rec: " + arvore.maior());
        
        System.out.println("Menor ra da arvore nrec: " + arvore.menor());
        System.out.println("Maior ra da arvore nrec: " + arvore.maior());
    }
    
    public void main() {
        exemplo1();
        exemplo2();
    }
}
