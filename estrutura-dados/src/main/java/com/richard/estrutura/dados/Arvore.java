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
    int size;
    
    public static <T> Arvore<T> inicializa() {
        Arvore<T> arvore = new Arvore<>();
        arvore.raiz = null;
        return arvore;
    }
    
    public void inserir(String info, T dados) {
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
                
                int comparacao = info.compareTo(aux.info);
                
                if (comparacao == 0) {
                    System.out.println("\nDado inserido já existe!");
                    return; 
                }
                
                if (comparacao > 0) {
                    // Valor e maior que o no atual caminha para a direita
                    aux = aux.direita;
                } else {
                    // Valor e menor que o no atual caminha para a esquerda
                    aux = aux.esquerda;
                }
            }
            
            if (ant.info.compareTo(info) < 0) {
                ant.direita = no;
            } else {
                ant.esquerda = no;
            }
        }
        
        size++;
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
    
    // tamanho
    public int length() {
        return size;
    }
    
    // Busca um no na arvore
    public T pesquisaArvore(String chave) {
        NoArvore<T> no = pesquisa(chave, raiz);
        if (no != null) {
            return no.dados;
        } else {
            return null;
        }
    }
    
    // Busca o menor item a esquerda da arvore modo recursivo
    public T menor() {
        return menorItem(raiz);
    }
    
    // Busca o maior item a esquerda da arvore modo recursivo
    public T maior() {
        return maiorItem(raiz);
    }
    
    // Busca o menor item a esquerda da arvore modo não recursivo
    public T menorFast() {
        NoArvore<T> no, ant;
        
        no = raiz;
        ant = raiz;
        
        while(no != null) {
            ant = no.esquerda != null ? no.esquerda : no;
            no = no.esquerda;
        }
        
        return (T) ant;
    }
    
    // Busca o maior item a esquerda da arvore modo não recursivo
    public T maiorFast() {
        NoArvore<T> no, ant;
        
        no = raiz;
        ant = raiz;
        
        while(no != null) {
            ant = no.direita != null ? no.direita : no;
            no = no.direita;
        }
        
        return (T) ant;
    }
    
    private T menorItem(NoArvore<T> no) {
        if (no == null) {
            return null;
        }
        
        if (no.esquerda == null) {
            return (T) no;
        }
        
        return (T) menorItem(no.esquerda);
    }
    
    private T maiorItem(NoArvore<T> no) {
        if (no == null) {
            return null;
        }
        
        if (no.direita == null) {
            return (T) no;
        }
        
        return (T) maiorItem(no.direita);
    }
    
    private void caminharEmOrdem(NoArvore<T> no) {
        if (no != null) {
            caminharEmOrdem(no.esquerda);
            System.out.print(no.toString());
            caminharEmOrdem(no.direita);
        }
    }
    
    private void caminharEmPreOrdem(NoArvore<T> no) {
        if (no != null) {
            System.out.print(no.toString());
            caminharEmPreOrdem(no.esquerda);
            caminharEmPreOrdem(no.direita);
        }
    }
    
    private void caminharEmPosOrdem(NoArvore<T> no) {
        if (no != null) {
            caminharEmPreOrdem(no.esquerda);
            caminharEmPreOrdem(no.direita);
            System.out.print(no.toString());
        }
    }
    
    private NoArvore<T> pesquisa(String chave, NoArvore<T> no) {
        if (no == null) {
            return null;
        } else if (chave.compareTo(no.info) < 0){
            return pesquisa(chave, no.esquerda);
        } else if (chave.compareTo(no.info) > 0){
            return pesquisa(chave, no.direita);
        } else {
            return no;
        }
    }
    
    private void excluir(int chave, NoArvore<T> no) {
        NoArvore<T> p;
        NoArvore<T> q;
        NoArvore<T> rp;
        NoArvore<T> f;
        NoArvore<T> s;
        
        p = no; // raiz
        
        size--;
    }
}
