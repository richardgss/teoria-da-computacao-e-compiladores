/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package com.richard.estrutura.dados;

import java.util.Scanner;

/**
 *
 * @author 32216450
 */
public class EstruturaDados {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int busca;
        int[] list;
        boolean achou;

        list = new int[5];
        
        for (int i=0; i<list.length; i++) {
            System.out.println("Digite um número: ");
            list[i] = scanner.nextInt();
        }
        
        System.out.println("Digite o número para a busca:");
        
        busca = scanner.nextInt();
        
        achou = false;
        for (int i=0; i<list.length; i++) {
            if (busca == list[i]) {
                achou = true;
                break;
            }
        }
        
        if (achou) {
            System.out.println("Elemento encontrado");
        } else {
            System.out.println("Elemento não encontrado");
        }
    }
}
