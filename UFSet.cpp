#include "UFSet.h"
/* El tipo UFNode* representa:
 *  1. un elemento de un UFSet (o sea, un nodo del árbol que contiene a todos los elementos del conjunto)
 *  2. al conjunto en su totalidad, si el nodo es la raíz del arbol
 *
 *  El nodo tiene un puntero a su elemento asociado en el campo element. 
 *  Deberán agregarse los campos necesarios para completar la representación.
 * 
Un conjunto es una colección de nodos conectados en un árbol, 
donde cada nodo apunta a su padre hasta llegar a la raíz, 
que es su propio padre. Por lo tanto, la raíz de un conjunto 
es el elemento distinguido del conjunto.

El campo parent del nodo siempre apunta a un nodo que es 
un representante válido del conjunto. Si se sigue el puntero parent desde cualquier nodo,
llega a la raíz del conjunto (elemento distinguido).

El rango se utiliza para optimizar las operaciones de unión. 
Al unir dos conjuntos, siempre se elige el representante del conjunto con un rango menor 
como el padre del representante del conjunto con un rango mayor. 
Esto ayuda a mantener el rango bajo y garantiza un buen rendimiento en las operaciones posteriores.
 */
struct UFNode {
/*  
 Invariantes de representacion:
--Cada nodo del conjunto conoce a su padre, y el elemento distinguido apunta a si mismo (parent apunta a sí misma).
--El representante de un conjunto es el elemento distinguido.
--Los conjuntos son disjuntos, lo que significa que no hay nodos compartidos entre conjuntos.
--Para cada nodo existente dentro de un conjunto todos deben terminar apuntando a la raiz del conjunto (Esto con la optimizacion)
*/
   ELEM_TYPE element;
   struct UFNode* parent;
   int rank; //para la optimizacion, ayuda a mejorar la eficiencia en el find y en union decidir el representante
};

/* 
 * Inicializa el UFSet ufset, cuyo valor asociado será value 
 */
UFSet createUFS(ELEM_TYPE value) {
   UFNode* ufset = new UFNode; // para asignar memoria
        ufset->element = value;
        ufset->parent = ufset; // el nodo es su propio padre
        ufset->rank = 0; // al inicializarse su rank es 0
        return ufset;
}

ELEM_TYPE elemUFS(UFSet ufset) {
    return ufset->element;
}

/*
 * Encuentra el elemento distinguido para el UFSet dado. 
 * Esta operación puede ser optimizada con la técnica de compresión de camino.
 UFSet findUF(UFSet elem) {
  //Implementacion sin compresion de camino
   // Encuentra la raíz siguiendo el camino hasta la raíz
   while (elem->parent != elem) {
         elem = elem->parent;
   }
   return elem; // Devuelve el representante
}
 */
UFSet findUFS(UFSet elem) {
  UFSet root = elem;
   // Encuentra la raíz siguiendo el camino hasta la raíz
   while (root->parent != root) {
         root = root->parent;
   }
        
   // Aplica la compresión de camino en el camino original
   while (elem != root) {
       UFSet next = elem->parent;
       elem->parent = root;
       elem = next;
   }//Luego los siguientes llamados a findUFS seran O(1)
        
   return root; // Devuelve el representante
}

/*
 * Calcula la unión entre los conjuntos ufset1 y ufset2. 
 * Esta operación puede ser optimizada con la técnica de unión por rango.
 */
 /*
     void unionUF(UFSet ufset1, UFSet ufset2){ 
     //Implementacion sin RANK 
     UFSet root2 = findUFS(ufset2);//Raiz del segundo conjunto 
     ufset1 -> parent = root2; //Su padre ahora es al conjunto que se unió
};*/
void unionUFS(UFSet ufset1, UFSet ufset2) {
   UFSet root1 = findUFS(ufset1); // raíz del primer conjunto
    UFSet root2 = findUFS(ufset2); // raíz del segundo conjunto

    if (root1 != root2) {
        if (root1->rank < root2->rank) {
            root1->parent = root2; // el segundo conjunto sea el padre del primero
        } else if (root1->rank > root2->rank) {
            root2->parent = root1; // el primer conjunto sea el padre del segundo
        } else { //Sus rangos son iguales al llegar a esta rama del else
            root2->parent = root1; // el primer conjunto sea el padre del segundo
            root1->rank++; //Aumenta porque son de igual tamaño, al unirlo aumenta
        }
    }
}

