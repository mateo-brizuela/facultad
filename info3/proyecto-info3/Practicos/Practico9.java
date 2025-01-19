package Practicos;

import java.util.Random;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.LinkedHashMap;

import Utils.HashTable.HashTable;
import Utils.BinaryHeap.BinaryHeap;

public class Practico9{
public static void main(String[] args) {
    BinaryHeap heap = new BinaryHeap(); //heap binario
    HashTable<Object, Object> hashTable = new HashTable<>(); // tabla hash
    //PARA UTILIZAR CON LIBRERIAS GENERICAS
    ArrayList<Object> arrayList = new ArrayList<>(); // ArrayList
    LinkedList<Object> linkedList = new LinkedList<>(); // LinkedList
    HashMap<Object, Object> hashMap = new HashMap<>(); // HashMap
    TreeMap<Object, Object> treeMap = new TreeMap<>(); // TreeMap
    LinkedHashMap<Object, Object> linkedHashMap = new LinkedHashMap<>();

    Random random = new Random();
    int menu_op = 0;
    var console = new Scanner(System.in);
    boolean exit = false;

    do{
        System.out.println("Se presenta un menu de opciones:\n");
        System.out.println(
                            "-------MONTICULO BINARIO-------\n"+
                            "1-Agregar x cantidad de numeros aleatorios\n"+
                            "2-Agregar elemento manualmente\n"+
                            "3-Extraer el elemento de mayor prioridad del heap (Eliminar Min)\n"+
                            "\n----------TABLA HASH-----------\n"+
                            "4-Agregar elemento a tabla hash\n"+
                            "5-Buscar elemento por clave\n"+
                            "6-Eliminar un elemento por su clave.\n"+
                            "\n-----GENERAL CON LIBRERIAS-----\n\n"+
                            "----ARRAYLIST DE UN OBJETO-----\n"+
                            "7-Agregar objeto al AreayList\n"+
                            "8-Imprimir ArrayList completo\n"+
                            "9-Imprimir elemento del ArrayList\n"+
                            "10-Borrar elemento del ArrayList\n"+
                            "\n----LINKEDLIST DE UN OBJETO----\n"+
                            "11-Agregar objeto al Linkedist\n"+
                            "12-Imprimir Linkedist completa\n"+
                            "13-Imprimir elemento de la Linkedist\n"+
                            "14-Borrar elemento de la Linkedist\n"+
                            "\n------HASHMAP DE UN OBJETO-----\n"+
                            "15-Agregar elemento al HashMap\n"+
                            "16-Imprimir HashMap completo\n"+
                            "17-Imprimir elemento del HashMap\n"+
                            "18-Borrar elemento del HashMap\n"+
                            "\n-----TREEMAP DE UN OBJETO------\n"+
                            "19-Agregar objeto al TreeMap\n"+
                            "20-Imprimir TreeMap completo\n"+
                            "21-Imprimir elemento del TreeMap\n"+
                            "22-Borrar un elemento del TreeMap\n"+
                            "\n--LINKEDHASHMAP DE UN OBJETO---\n"+
                            "23-Agregar objeto al LinkedHashMap\n"+
                            "24-Imprimir LinkedHashMap completo\n"+
                            "25-Imprimir elemento del LinkedHashMap\n"+
                            "26-Borrar elemento del LinkedHashMap\n"+
                            "\n-------------------------------\n"+
                            "27-Salir\n");
        System.out.println("Seleccione una opcion:");
        menu_op = console.nextInt();
    switch (menu_op) {
        case 1:
            System.out.println("¿Cuantos numeros desea agregar?:");
            int n1=console.nextInt();
        // Agregar 10 números aleatorios en el rango de 0 a 100
            for (int i = 0; i < n1; i++) {
            int numeroAleatorio = random.nextInt(100); // Genera un número aleatorio en el rango [0, 100)
            heap.insert(numeroAleatorio); // Inserta el número en el montículo
            }
        // Imprimir el montículo
            System.out.println("\nContenido del montículo después de las inserciones:");
            heap.printHeap();
        break;

        case 2:
            System.out.println("Ingrese el numero que desea insertar:");
            Integer nAgregar = console.nextInt();
            heap.insert(nAgregar);
        // Imprimir el montículo
            System.out.println("\nContenido del montículo después de la insercion:");
            heap.printHeap();
       
        break;

        case 3:
        // Extraer el mínimo
        System.out.println("Contenido del montículo antes de la eliminación:");
        heap.printHeap();
        Integer min = heap.eliminateMin();
        System.out.println("\nElemento extraído (mínimo): " + min);

        // Imprimir el montículo después de la extracción
        System.out.println("\nContenido del montículo después de extraer el mínimo:");
        heap.printHeap();
        break;

        case 4:
        System.out.println("\nIngrese la clave (numero entero o cadena):");
        console.nextLine();
        String keyInput = console.nextLine();
        // Convertir el valor en número si es posible
        Object key;
            try {
                key = Integer.parseInt(keyInput);
            } catch (NumberFormatException e) {
                key = keyInput; // Si no es número, se trata como cadena
                }
 
        System.out.println("Ingrese el valor (puede ser número o cadena):");
        String valueInput = console.nextLine();

        // Convertir el valor en número si es posible
        Object value;
            try {
                value = Integer.parseInt(valueInput);
            } catch (NumberFormatException e) {
                value = valueInput; // Si no es número, se trata como cadena
            }

        hashTable.put(key, value);
        System.out.println("\nElemento ingresado - Clave: " + key + ", Valor: " + value);

        // Mostrar valores ingresados por buckets
        System.out.println("\nValores ingresados en la tabla hash:");
        for (int i = 0; i < hashTable.getBucketsSize(); i++) {
            hashTable.printBucket(i); // Imprimir los contenidos de cada bucket
        }
        System.out.println();
        break;

        case 5:
         // Mostrar valores ingresados por buckets
         System.out.println("\nValores ingresados en la tabla hash:");
         for (int i = 0; i < hashTable.getBucketsSize(); i++) {
             hashTable.printBucket(i); // Imprimir los contenidos de cada bucket
         }
         System.out.println();

        System.out.println("\nIngrese la clave que desea buscar:");
        console.nextLine();  // Limpiar el buffer
        String searchKeyInput = console.nextLine();
        
        // Convertir el valor en número si es posible
        Object searchKey;
            try {
                searchKey = Integer.parseInt(searchKeyInput);
            } catch (NumberFormatException e) {
                searchKey = searchKeyInput; // Si no es número, se trata como cadena
            }

        // Buscar el elemento en la tabla hash
        Object searchResult = hashTable.search_element(searchKey);
            if (searchResult != null) {
                System.out.println("Elemento encontrado - [Clave: " + searchKey + ", Valor: " + searchResult+"]\n");
            } else {
                System.out.println("Elemento no encontrado para la clave: " + searchKey + "\n");
                }
        break;

        case 6:
          // Mostrar valores ingresados por buckets
          System.out.println("\nValores ingresados en la tabla hash:");
          for (int i = 0; i < hashTable.getBucketsSize(); i++) {
              hashTable.printBucket(i); // Imprimir los contenidos de cada bucket
          }
          System.out.println();
 
        System.out.println("\nIngrese la clave (número entero o cadena) del elemento a eliminar:");
        console.nextLine();
        String keyInput2 = console.nextLine();
        
        // Convertir la clave en número si es posible
        Object key2;
        try {
            key2 = Integer.parseInt(keyInput2); // Si es un número, se convierte
        } catch (NumberFormatException e) {
            key2 = keyInput2; // Si no es número, lo tratamos como cadena
        }
        
        // Llamar al método remove para eliminar el elemento
        hashTable.remove(key2);
        
        // Mostrar los valores por cada bucket después de la eliminación
        System.out.println("\nValores restantes en la tabla hash:");
        for (int i = 0; i < hashTable.getBucketsSize(); i++) {
            hashTable.printBucket(i); // Imprimir los contenidos de cada bucket
        }
        
        break;

          // --- ArrayList ---
        case 7:
            System.out.println("Ingrese el objeto a agregar al ArrayList:");
            console.nextLine();
            String objArrayList = console.nextLine();
            arrayList.add(objArrayList);
            System.out.println();
        break;

        case 8:
            System.out.println("ArrayList completo: " + arrayList);
            System.out.println();
        break;

        case 9:
            System.out.println("Ingrese el índice del elemento a imprimir:");
            int indexArrayList = console.nextInt();
            System.out.println("Elemento en el índice " + indexArrayList + ": " + arrayList.get(indexArrayList));
            System.out.println();
        break;

        case 10:
            System.out.println("Ingrese el índice del elemento a borrar:");
            int removeIndex = console.nextInt();
            System.out.println("Elemento en el índice " + removeIndex + ": " + arrayList.get(removeIndex));
            arrayList.remove(removeIndex);
            System.out.println("Elemento borrado.");
            System.out.println();
        break;

      // --- LinkedList ---
        case 11:
            System.out.println("Ingrese el objeto a agregar al LinkedList:");
            console.nextLine();
            String objLinkedList = console.nextLine();
            linkedList.add(objLinkedList);
            System.out.println();
        break;

        case 12:
            System.out.println("LinkedList completo: " + linkedList);
            System.out.println();
        break;

        case 13:
            System.out.println("Ingrese el índice del elemento a imprimir:");
            int indexLinkedList = console.nextInt();
            System.out.println("Elemento en el índice " + indexLinkedList + ": " + linkedList.get(indexLinkedList));
            System.out.println();
        break;

        case 14:
            System.out.println("Ingrese el índice del elemento a borrar:");
            int removeIndexLinkedList = console.nextInt();
            System.out.println("Elemento en el índice " + removeIndexLinkedList + ": " + linkedList.get(removeIndexLinkedList));
            System.out.println();
            linkedList.remove(removeIndexLinkedList);
            System.out.println("Elemento borrado.");
            System.out.println();
        break;

      // --- HashMap ---
        case 15:
        System.out.println("Ingrese la clave (puede ser cualquier tipo) para agregar:");
        console.nextLine();
        String keyInputHashMap = console.nextLine();
        System.out.println("Ingrese el valor (puede ser cualquier tipo) para agregar:");
        String valueInputHashMap = console.nextLine();

        // Convertir clave y valor a tipos de datos genéricos
        Object keyHashMap;
        try {
            keyHashMap = Integer.parseInt(keyInputHashMap);
        } catch (NumberFormatException e) {
            keyHashMap = keyInputHashMap; // Si no es un número, se usa como cadena
        }

        Object valueHashMap;
        try {
            valueHashMap = Integer.parseInt(valueInputHashMap);
        } catch (NumberFormatException e) {
            valueHashMap = valueInputHashMap;
        }

        // Agregar al HashMap
        hashMap.put(keyHashMap, valueHashMap);
        break;

        case 16:
            System.out.println("HashMap completo: " + hashMap);
            System.out.println();
        break;

        case 17:
        System.out.println("Ingrese la clave del elemento a imprimir:");
        console.nextLine();
        String searchKeyHashMap = console.nextLine();
        Object searchKeyHashMapConverted;
        try {
            searchKeyHashMapConverted = Integer.parseInt(searchKeyHashMap);
        } catch (NumberFormatException e) {
            searchKeyHashMapConverted = searchKeyHashMap; // Si no es un número, se usa como cadena
        }

        if (hashMap.containsKey(searchKeyHashMapConverted)) {
            System.out.println("Elemento encontrado: [Clave: " + searchKeyHashMapConverted + ", Valor: " + hashMap.get(searchKeyHashMapConverted) + "]");
        } else {
            System.out.println("Elemento no encontrado.");
        }
        break;

        case 18:
        System.out.println("Ingrese la clave del elemento a eliminar:");
        console.nextLine();
        String deleteKeyHashMap = console.nextLine();
        Object deleteKeyHashMapConverted;
        try {
            deleteKeyHashMapConverted = Integer.parseInt(deleteKeyHashMap);
        } catch (NumberFormatException e) {
            deleteKeyHashMapConverted = deleteKeyHashMap; // Si no es un número, se usa como cadena
        }

        hashMap.remove(deleteKeyHashMapConverted);
        break;

      // --- TreeMap ---
        case 19:
        System.out.println("Ingrese la clave (puede ser cualquier tipo) para agregar al TreeMap:");
        console.nextLine();
        String keyInputTreeMap = console.nextLine();
        System.out.println("Ingrese el valor (puede ser cualquier tipo) para agregar al TreeMap:");
        String valueInputTreeMap = console.nextLine();

        // Convertir la clave y el valor en tipos genéricos
        Object keyTreeMap;
        try {
            keyTreeMap = Integer.parseInt(keyInputTreeMap);
        } catch (NumberFormatException e) {
            keyTreeMap = keyInputTreeMap; // Si no es un número, se usa como cadena
        }

        Object valueTreeMap;
        try {
            valueTreeMap = Integer.parseInt(valueInputTreeMap);
        } catch (NumberFormatException e) {
            valueTreeMap = valueInputTreeMap;
        }

        treeMap.put(keyTreeMap, valueTreeMap);
        break;

        case 20:
          System.out.println("TreeMap completo: " + treeMap);
          System.out.println();
        break;

        case 21:
        System.out.println("Ingrese la clave para imprimir del TreeMap:");
        console.nextLine();
        String searchKeyTreeMap = console.nextLine();

        // Convertir la clave a tipo genérico
        Object searchKeyTreeMapConverted;
        try {
            searchKeyTreeMapConverted = Integer.parseInt(searchKeyTreeMap);
        } catch (NumberFormatException e) {
            searchKeyTreeMapConverted = searchKeyTreeMap; // Si no es un número, se usa como cadena
        }

        if (treeMap.containsKey(searchKeyTreeMapConverted)) {
            System.out.println("Elemento encontrado: [Clave: " + searchKeyTreeMapConverted + ", Valor: " + treeMap.get(searchKeyTreeMapConverted) + "]");
        } else {
            System.out.println("Elemento no encontrado.");
        }
        break;

        case 22:
        System.out.println("Ingrese la clave del elemento a borrar:");
        console.nextLine();
        String deleteKeyTreeMap = console.nextLine();

        // Convertir la clave a tipo genérico
        Object deleteKeyTreeMapConverted;
        try {
            deleteKeyTreeMapConverted = Integer.parseInt(deleteKeyTreeMap);
        } catch (NumberFormatException e) {
            deleteKeyTreeMapConverted = deleteKeyTreeMap; // Si no es un número, se usa como cadena
        }

        treeMap.remove(deleteKeyTreeMapConverted);
        break;

      // --- LinkedHashMap ---
        case 23:
        System.out.println("Ingrese la clave (puede ser de cualquier tipo) para agregar al LinkedHashMap:");
        console.nextLine();
        String keyInputLinkedHashMap = console.nextLine();
        System.out.println("Ingrese el valor (puede ser de cualquier tipo) para agregar al LinkedHashMap:");
        String valueInputLinkedHashMap = console.nextLine();

        // Convertir la clave y el valor a tipos genéricos
        Object keyLinkedHashMap;
        try {
            keyLinkedHashMap = Integer.parseInt(keyInputLinkedHashMap);
        } catch (NumberFormatException e) {
            keyLinkedHashMap = keyInputLinkedHashMap; // Si no es un número, se usa como cadena
        }

        Object valueLinkedHashMap;
        try {
            valueLinkedHashMap = Integer.parseInt(valueInputLinkedHashMap);
        } catch (NumberFormatException e) {
            valueLinkedHashMap = valueInputLinkedHashMap;
        }
        linkedHashMap.put(keyLinkedHashMap, valueLinkedHashMap);
        break;

        case 24:
          System.out.println("LinkedHashMap completo: " + linkedHashMap);
          System.out.println();
        break;

        case 25:
      System.out.println("Ingrese la clave para imprimir del LinkedHashMap:");
      console.nextLine();
      String searchKeyLinkedHashMap = console.nextLine();

      // Convertir la clave a tipo genérico
      Object searchKeyLinkedHashMapConverted;
      try {
          searchKeyLinkedHashMapConverted = Integer.parseInt(searchKeyLinkedHashMap);
      } catch (NumberFormatException e) {
          searchKeyLinkedHashMapConverted = searchKeyLinkedHashMap; // Si no es un número, se usa como cadena
      }

      if (linkedHashMap.containsKey(searchKeyLinkedHashMapConverted)) {
          System.out.println("Elemento encontrado: [Clave: " + searchKeyLinkedHashMapConverted + ", Valor: " + linkedHashMap.get(searchKeyLinkedHashMapConverted) + "]");
      } else {
          System.out.println("Elemento no encontrado.");
      }
        break;

        case 26:
      System.out.println("Ingrese la clave del elemento a borrar:");
      console.nextLine();
      String deleteKeyLinkedHashMap = console.nextLine();

      // Convertir la clave a tipo genérico
      Object deleteKeyLinkedHashMapConverted;
      try {
          deleteKeyLinkedHashMapConverted = Integer.parseInt(deleteKeyLinkedHashMap);
      } catch (NumberFormatException e) {
          deleteKeyLinkedHashMapConverted = deleteKeyLinkedHashMap; // Si no es un número, se usa como cadena
      }

      linkedHashMap.remove(deleteKeyLinkedHashMapConverted);
        break;

        case 27:
          exit = true;
        break;

      default:
          System.out.println("Opción inválida.");
        }
        
    }while (exit != true);
    console.close();
    }
      
}    
    