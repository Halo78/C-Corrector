#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "../Include/Element.h"

void element_print (element_t e) {
  printf("%s : %d; ", e.key,e.value);
}

void element_init (element_t* e) {
  e->value=0; e->key=NULL;
}

int element_equal(element_t* e1, element_t* e2) {
  return key_equal(e1->key,e2->key) && value_equal(e1->value,e1->value);
}

int value_equal(value_t v1, value_t v2) {
  return v1==v2;
}

int key_equal(keys_t k1, keys_t k2) {
  return strcasecmp(k1,k2)==0;
}

element_t element_clone(element_t e) {
  element_t clone;
  clone.value=e.value;
  clone.key = strdup(e.key);
  return clone;
}

element_t element_new(keys_t key, value_t value) {
  element_t e;
  e.key=strdup(key);
  e.value=value;
  return e;
}

element_t element_delete(element_t e) {
  if (e.key) free(e.key);
  e.key=NULL;
  e.key=0;
  return e;
}

void element_fprint (FILE* fd, element_t e) {
  fprintf(fd,"%s : %d ; ", e.key,e.value);
}

int element_compare(element_t* e1, element_t* e2) {
  return e1->value>e2->value ? 1 : e1->value==e2->value ? 0 : -1;
}
