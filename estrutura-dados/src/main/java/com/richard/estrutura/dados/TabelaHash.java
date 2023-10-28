/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.richard.estrutura.dados;

/**
 *
 * @author 32216450
 */
public class TabelaHash<T> {
   private Arvore<T>[] tabela;
   
   public TabelaHash() {
       tabela = new Arvore[26];
       // Inicializa todas as arvores
       for (int i=0; i<tabela.length; i++) {
           tabela[i] = Arvore.inicializa();
       }
   }
   
    private int funcaoHash(String nome)
    {
        return nome.toLowerCase().charAt(0) -97;
    }
    
    public void inserir(String nome, T valor)
    {
        int pos = funcaoHash(nome);
        tabela[pos].inserir(nome, valor);
    }
    
    public void imprimir()
    {
        for (int i = 0; i < tabela.length; i++)
        {
            if (tabela[i] != null)
            {
                System.out.println("tabela["+ i + " - "+(char)(i+65)+"]{");
                tabela[i].emOrdem();
                System.out.println("}");
//                System.out.println("\n[" + tabela[i].toUpperCase().charAt(0) + "]");
//                System.out.println("\n[" + (char)(i+65) + "]");
//                System.out.println(" - " + tabela[i]);
            }
        }
    }
    
    public T buscar(String nome)
    {
        int pos = funcaoHash(nome);
        if (tabela[pos] != null) {
            return tabela[pos].pesquisaArvore(nome);
        }
        
        return null;
    }
}
