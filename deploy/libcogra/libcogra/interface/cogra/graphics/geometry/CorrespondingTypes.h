/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_GEOMETRY_CORESSPONDINGTYPES_H_
#define COGRA_GRAPHICS_GEOMETRY_CORESSPONDINGTYPES_H_
namespace cogra
{
    namespace graphics
    {
        namespace geometry
        {
            template<class VALUE_TYPE, class VECTOR_TYPE>
            struct getCorrespondingMatrixType
            { };

            template<class VALUE_TYPE>
            struct getCorrespondingMatrixType<VALUE_TYPE, glm::vec<2, VALUE_TYPE, glm::qualifier::defaultp> >
            {
                typedef glm::mat<2, 2, VALUE_TYPE, glm::qualifier::defaultp> matrix_type;
            };

            template<class VALUE_TYPE>
            struct getCorrespondingMatrixType<VALUE_TYPE, glm::vec<3, VALUE_TYPE, glm::qualifier::defaultp> >
            {
                typedef glm::mat<3, 3, VALUE_TYPE, glm::qualifier::defaultp> matrix_type;
            };

            template<class VALUE_TYPE>
            struct getCorrespondingMatrixType<VALUE_TYPE, glm::vec<4, VALUE_TYPE, glm::qualifier::defaultp> >
            {
                typedef glm::mat<4, 4, VALUE_TYPE, glm::qualifier::defaultp> matrix_type;
            };

            template<class VALUE_TYPE, class VECTOR_TYPE>
            struct getUpperDimensionVectorType
            { };

            template<class VALUE_TYPE>
            struct getUpperDimensionVectorType<VALUE_TYPE, glm::vec<2, VALUE_TYPE, glm::qualifier::defaultp> >
            {
                typedef glm::vec<3, VALUE_TYPE, glm::qualifier::defaultp> vector_type;
            };

            template<class VALUE_TYPE>
            struct getUpperDimensionVectorType<VALUE_TYPE, glm::vec<3, VALUE_TYPE, glm::qualifier::defaultp> >
            {
                typedef glm::vec<4, VALUE_TYPE, glm::qualifier::defaultp> vector_type;
            };
        }
    }
}

#endif
