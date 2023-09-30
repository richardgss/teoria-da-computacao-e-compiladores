/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.richard.estrutura.dados;

/**
 *
 * @author 32216450
 * @param <T> Tipo da arvore
 */
public class Arvore<T> {
    NoArvore<T> raiz;
    
    public static <T> Arvore<T> inicializa() {
        Arvore<T> arvore = new Arvore<>();
        arvore.raiz = null;
        return arvore;
    }
    
    public void inserir(int info, T dados) {
        NoArvore<T> no = new NoArvore<>();
        no.info = info;
        no.dados = dados;
        no.esquerda = null;
        no.direita = null;
        
        if (raiz == null) {
            raiz = no;
        } else {
            // Inicializa variaveis de busca
            NoArvore<T> aux;
            NoArvore<T> ant;
            
            aux = raiz;
            ant = null;
            
            while (aux != null) {
                // Faz a busca do lugar ao qual ao qual deve ser inserido o nó
                ant = aux;
                
                if (aux.info == info) {
                    System.out.println("\nDado inserido já existe!");
                    return; 
                }
                
                if (info > aux.info) {
                    // Valor e maior que o no atual caminha para a direita
                    aux = aux.direita;
                } else {
                    // Valor e menor que o no atual caminha para a esquerda
                    aux = aux.esquerda;
                }
            }
            
            if (ant.info < info) {
                ant.direita = no;
            } else {
                ant.esquerda = no;
            }
        }
    }
   
    // infixa
    public void emOrdem() {
        caminharEmOrdem(raiz);
        System.out.println("");
    }
    
    // prefixa
    public void preOrdem() {
        caminharEmPreOrdem(raiz);
        System.out.println("");
    }
    
    // posfixa
    public void posOrdem() {
        caminharEmPosOrdem(raiz);
        System.out.println("");
    }
    
    // Busca um no na arvore
    public T pesquisaArvore(int chave) {
        NoArvore<T> no = pesquisa(chave, raiz);
        if (no != null) {
            return no.dados;
        } else {
            return null;
        }
    }
    
    void caminharEmOrdem(NoArvore<T> no) {
        if (no != null) {
            caminharEmOrdem(no.esquerda);
            System.out.print(no.toString());
            caminharEmOrdem(no.direita);
        }
    }
    
    void caminharEmPreOrdem(NoArvore<T> no) {
        if (no != null) {
            System.out.print(no.toString());
            caminharEmPreOrdem(no.esquerda);
            caminharEmPreOrdem(no.direita);
        }
    }
    
    void caminharEmPosOrdem(NoArvore<T> no) {
        if (no != null) {
            caminharEmPreOrdem(no.esquerda);
            caminharEmPreOrdem(no.direita);
            System.out.print(no.toString());
        }
    }
    
    NoArvore<T> pesquisa(int chave, NoArvore<T> no) {
        if (no == null) {
            return null;
        } else if (chave < no.info){
            return pesquisa(chave, no.esquerda);
        } else if (chave > no.info){
            return pesquisa(chave, no.direita);
        } else {
            return no;
        }
    }
    
    void excluir(int chave, NoArvore<T> no) {
        NoArvore<T> p;
        NoArvore<T> q;
        NoArvore<T> rp;
        NoArvore<T> f;
        NoArvore<T> s;
        
        p = no; // raiz
        
        
    }
}
