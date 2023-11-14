# TP-Estrd
/* 
 * Inicializa el UFSet ufset, cuyo valor asociado será value 
 */
UFSet createUFS(ELEM_TYPE value) {
   UFNode* ufset = new UFNode; // para asignar memoria
        ufset->element = value;
        ufset->parent = ufset; // el nodo es su propio padre
        ufset->rank = 0; // al inicializarse su rank (altura de nodos) es 0
        return ufset;
}

ELEM_TYPE elemUFS(UFSet ufset) {
    return ufset->element;
}

/*
 * Encuentra el elemento distinguido para el UFSet dado. 
 * Esta operación puede ser optimizada con la técnica de compresión de camino.
 */
UFSet findUFS(UFSet elem) {
  UFSet root = elem;
   // Encuentra la raíz siguiendo el camino hasta la raíz
   while (root->parent != root) {
         root = root->parent;
   }
        
   // Aplica la compresión de camino en el camino original
   //cambia el padre del elemento mientras entre en la condicion while 
   while (elem != root) {
       UFSet next = elem->parent;
       elem->parent = root;
       elem = next;
   }
        
   return root; // Devuelve el representante
}

Equipo distinguido(UFSet elem) {
  UFSet root = findUFS(elem);
  return root->element; // Devuelve el padre
}




/*
 * Calcula la unión entre los conjuntos ufset1 y ufset2. 
 * Esta operación puede ser optimizada con la técnica de unión por rango.
 */
void unionUF(UFSet ufset1, UFSet ufset2){ //Implementacion sin RANK
    UFSet root2 = findUFS(ufset2);//Raiz del segundo conjunto 
    ufset1 -> parent = root2; //Su padre ahora es al conjunto que se unió

};


void unionUFS(UFSet ufset1, UFSet ufset2) {
   UFSet root1 = findUFS(ufset1); // busco la raíz del primer conjunto
   UFSet root2 = findUFS(ufset2); // busco la raíz del segundo conjunto

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
