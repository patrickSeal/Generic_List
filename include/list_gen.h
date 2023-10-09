/*
    A generic list, where you can save all your kinds of data you can think of, even lists of lists of lists of lists of ...

    [char **element_types in Gen_List is still work in progress]
*/

typedef struct list_entry{
    void *data;
    char *type;
    struct list_entry *next;
} List_Element;

typedef struct list_instance{
    List_Element *head;
    int size;
    char **element_types;
    int amount_of_types;
} Gen_List;

/*
    This Method adds your struct or variable to a list, at the end of the list.
    [Recommended]: 'type' should be the name of your struct or the data type of your variable.

    @param Gen_List *list   :   pointer to the Gen_List you want to use.
    @param void     *ep     :   pointer to your struct, union or variable.
    @param char     *type   :   name of the data you want to add.
*/
extern int addElement(Gen_List *list, void *ep, char *type);

/*
    This Method inserts data at a certain index in a specified list.
    [Recommended]: 'type' should be the struct name or variable data type!
*/
extern int insertElement(Gen_List *list, void *ep, char *type, int index);

/*
    WARNING: This Method removes an element permanently out of Memory!!!

    @param Gen_List *list   :   pointer to the Gen_List to be used
    @param int      index   :   index of the Element in the list to be removed

    @return
        - on success: 0
        - list is empty: -1
        - index out of bounds: -2
*/
extern int removeElement(Gen_List *list, int index);

/*
    This Method returns a pointer to the data saved at a specific index position in the list.

    @param Gen_List *list   :   pointer to the Gen_List to be used
    @param int      index   :   index of the Element you want the data of

    @return
        - on success: pointer to the data
        [WARNING]: before you use the data you have to make sure you interpret it with the right type!!!
        - on failure: returns a NULL pointer

    [WARNING]: If you want to use your Gen_List for multiple kinds of data, you have to distinguish your
    data, by type. Otherwise you could get corrputed data.

    [RECOMMENDED]: If you don't know what you are doing you should use a Gen_List with only one type.

    *** The code in your program may look like this ***
    ...
        char *type = getType(your_list, your_index); // saves the type of the element you want
        // instantiate different pointer variables depending on your saved object types
        // e.g.:    struct cat..., struct dog..., ...
        struct cat *cat_pointer; struct dog *dog_pointer; ...;

        if(!strcmp(type, "struct cat")){
            cat_pointer = getElement(your_list, your_index);
        }else if(...){...}
        else{
            default state means you have no pointer to get the value
            this case should not be used in general, because it can lead to corrupted data!
            [RECOMMEND]: Cleaning the list.
        }
*/
extern void *getElement(Gen_List *list, int index);

/*
    This Method returns the type of an Element.
    May be used if you want to save multiple kinds of struct, union or data types.
    [WARNING]: If your Gen_List saves multiple kinds of data, you need this Method to distinguish them from one another!!!
*/
extern char *getType(Gen_List *list, int index);

/*
    This Method returns the size (length) of a Gen_List.

    @param Gen_List *list   :   pointer to the Gen_List you want to use.
*/
extern int getSize(Gen_List *list);

/*
    This Method prints the list in its order.
    @param Gen_List *list   :   Gen_List to be printed.
*/
extern int printList(Gen_List *list);

/*
    Constructor Method:
    Instantiates a new Gen_List with default values.

    @return pointer to the newly created Gen_List

    [WARNING]: It is not recommended to create a Gen_List without this constructor method.
    Other Methods may not work properly!
*/
extern Gen_List *new_Gen_List();
