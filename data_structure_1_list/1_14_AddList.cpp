#include "def.h"
#include "my.h"
int main() {
    LISTS Lists;
    int n, e;
    char name[30];
    Lists.length = 0;
    scanf("%d", &n);
    while (n--) {
        scanf("%s", name);
        AddList(Lists, name);
        scanf("%d", &e);
        while (e) {
            ListInsert(Lists.elem[Lists.length - 1].L, Lists.elem[Lists.length - 1].L.length + 1, e);
            scanf("%d", &e);
        }
    }
    for (n = 0; n < Lists.length; n++) {
        printf("%s ", Lists.elem[n].name);
        ListTraverse(Lists.elem[n].L);
        putchar('\n');
    }
    return 1;
}