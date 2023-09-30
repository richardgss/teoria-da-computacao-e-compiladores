/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.richard.estrutura.dados;

/**
 *
 * @author 32216450
 */
public class Aluno {
    public int ra;
    public String nome;
    
    public Aluno(int ra, String nome) {
        this.nome = nome;
    }
    
    @Override
    public String toString() {
        return "{ nome: " + nome + ", ra: " + ra + " }";
    }
}
