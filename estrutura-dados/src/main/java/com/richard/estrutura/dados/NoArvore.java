/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.richard.estrutura.dados;

/**
 *
 * @author 32216450
 * @param <T> Tipo dos dados da arvore
 */
public class NoArvore<T> {
    int info;
    T dados;
    NoArvore esquerda;
    NoArvore direita;
    
    @Override
    public String toString() {
        if (dados != null) {
            return "->" + info + ": " + dados;
        } else {
            return "->" + info;
        }
    }
}
