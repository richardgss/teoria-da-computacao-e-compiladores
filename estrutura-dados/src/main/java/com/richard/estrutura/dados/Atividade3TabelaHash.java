/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.richard.estrutura.dados;

/**
 *
 * @author 32216450
 */
public class Atividade3TabelaHash {
    
    public void main() {
        System.out.println("Rodou");

        TabelaHash<Aluno> tabelaHash = new TabelaHash<>();
        tabelaHash.inserir("Richard", new Aluno(150, "Richard"));
        tabelaHash.inserir("Lucas", new Aluno(100, "Lucas"));
        tabelaHash.inserir("Alexandre", new Aluno(50, "Alexandre"));
        tabelaHash.inserir("Ana Clara", new Aluno(120, "Ana Clara"));
        tabelaHash.inserir("Galadriel", new Aluno(130, "Galadriel"));
        tabelaHash.inserir("Azazel", new Aluno(250, "Azazel"));
        
        tabelaHash.imprimir();
        
        Aluno aluno = tabelaHash.buscar("Richard");
        if (aluno != null) {
            System.out.println("Aluno encontrado: " + aluno);
        } else {
            System.out.println("Aluno não encontrado!");
        }
    }
}
