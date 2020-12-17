#ifndef _ALGEBRA_VECTEUR_HPP_
#define _ALGEBRA_VECTEUR_HPP_
# include <vector>
# include <cstdlib>

namespace Algebra
{
    class Vecteur : public std::vector<double>
    {
    public:
        Vecteur() : proxy_norm(-1)
        {}
        Vecteur( size_t dim ) 
            :   std::vector<double>(dim),
                proxy_norm(-1)
        {}
        Vecteur( size_t dim, double val )
            :   std::vector<double>(dim,val),
                proxy_norm(-1)
        {}
        Vecteur( std::initializer_list<double>& l_init ) 
            :   std::vector<double>(l_init),
                proxy_norm(-1)
        {}
        Vecteur( const Vecteur& u ) = default;
        Vecteur( Vecteur&& u ) = default;
        ~Vecteur() = default;

        Vecteur& operator = ( const Vecteur& u ) = default;
        Vecteur& operator = ( Vecteur&& u      ) = default;
        
        double norm() const;
        bool operator <  ( const Vecteur& u ) const;
        bool operator >  ( const Vecteur& u ) const;
        bool operator <= ( const Vecteur& u ) const;
        bool operator >= ( const Vecteur& u ) const;
        bool operator == ( const Vecteur& u ) const;
        bool operator != ( const Vecteur& u ) const;
    private:
        mutable double proxy_norm;
    };
}

#endif
