/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.richard.estrutura.dados;

/**
 *
 * @author 32216450
 */
public class Atividade1BuscaBinaria {
    
    static int cont;
    
    public static int buscaBinaria(int vet [], int x, int inicio, int fim) {
        cont++;
        int meio = (inicio + fim) / 2;
        if(inicio > fim) {
            return -1;
        }
        if(vet[meio] == x) {
            return meio;
        }
        if(x < vet[meio]) {
            return buscaBinaria(vet,x,inicio,meio-1);
        }
        return buscaBinaria(vet,x,meio+1,fim);
    }
    
    public void main() {
        Aluno a = new Aluno(1010, "Alexandre"); 
        System.out.println(a);

        int vet [] = new int[1000];

        for(int i = 0;i < 1000; i++) {
            vet[i] = i;
        }

	int pos = buscaBinaria(vet,30,0,vet.length-1);

        if(pos == -1) {
            System.out.println("O numero não foi encotrado no vetor");
        } else {
            System.out.println("O numero foi encontrado na posicao "+pos);
        }

        System.out.println("Quantidade de passos "+cont);
    }
}
