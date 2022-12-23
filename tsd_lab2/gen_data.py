from random import randint

N = 700

def generate_perform(dest):
    THEATRES = ["Mariinskiy","Bolshoi", "Vahtangova", "MXAT", "Malyi theatre", "Lenkom", "Ekaterinburgskiy",
                "Mayakovskogo theatre"]
    for i in THEATRES:
        print(len(i), end = " ")
        
    PERFORM = ["Chaika", "Kolobok", "Shelkunchik", "LaLalend", "Matriza", "Terminator", "Planeta bur",
               "Anna Karenina", "Alenkiy zvetochek", "Hamlet", "Petya i Volk"]
    print()
    for i in PERFORM:
        print(len(i), end = " ")
    
    Director = ["Haidai", "Bondarchuck", "Aalda", "Beicon", "Bird", "Garanina", "Heller", "Con"]
    
    price_range = range(500, 10000)
    
    Type = ["adults", "kids", "musical"]
    
    GenreA = ["play", "drama", "comedy"]
    
    GenreK = ["play", "fairytale"]
    Kage = range(0, 13)
    Ktime_range = range(44, 90)
    
        
    Composers = ["Hurwitz", "Kern", "Vasilyev", "Dashkevich", "Berlin", "Gershvin", "Sai", "Low", "Rogers", 
               "Frimle", "Addler", "Andersson", "Berje", "Gold"]
    
    Country = ["Russia", "USA", "UK", "Australia", "France", "Italy", "Spain", "Ireland", "Germany"]
    Mmin_age = range(0, 19)
    Mtime_range = range(44, 151)
    
    for i in range(N):
        dest.write(str( THEATRES[randint(0, len(THEATRES) - 1)] ) + "\n" )
        dest.write(str( PERFORM[randint(0, len(PERFORM) - 1)] ) + "\n" )
        dest.write(str( Director[randint(0, len(Director) - 1)] ) + "\n" )
        
        prmin = price_range[ randint(0, len(price_range) - 1)]
        prmax = prmin + price_range[ randint(0, len(price_range) - 1)]
        
        dest.write(str(prmin) + " " + str(prmax) + "\n" )
        
        typee = Type[ randint(0, len(Type) - 1) ]
        
        dest.write(typee + "\n" )
        
        if typee == "adults":
            dest.write(str( GenreA[randint(0, len(GenreA) - 1)] ) + "\n" )
        elif typee == "kids":
            dest.write(str( GenreK[randint(0, len(GenreK) - 1)] ) + "\n" )
            dest.write(str( Kage[randint(0, len(Kage) - 1)] ) + "\n" )
            dest.write(str( Ktime_range[randint(0, len(Ktime_range) - 1)] ) + "\n" )
        elif typee == "musical":
            dest.write(str( Composers[randint(0, len(Composers) - 1)] ) + "\n" )
            dest.write(str( Country[randint(0, len(Country) - 1)] ) + "\n" )
            dest.write(str( Mmin_age[randint(0, len(Mmin_age) - 1)] )  + "\n" )
            dest.write(str( Mtime_range[randint(0, len(Mtime_range) - 1)] ) + "\n" )
        
with open("data700.txt", "w") as dst:
    generate_perform(dst)
    