// STL vector containers (use option -s to remove STL dependency)
#import "stlvector.h"


#define SOAP_NAMESPACE_OF_ns1	"urn:rm"
//gsoap ns1   schema namespace:	urn:rm
//gsoap ns1   schema form:	qualified


/// Primitive built-in type "xs:anyURI"
typedef std::string xsd__anyURI;

//  Forward declaration of class ns1__relation.
class ns1__relation;

//  Forward declaration of class ns1__body.
class ns1__body;

//  Forward declaration of class ns1__header.
class ns1__header;

//  Forward declaration of class ns1__transport.
class ns1__transport;

//  Forward declaration of class _ns1__dataRQ.
class _ns1__dataRQ;

//  Forward declaration of class _ns1__dataRS.
class _ns1__dataRS;
/// "urn:rm":relation is a complexType.
/// class ns1__relation operations:
/// - soap_new_ns1__relation(soap*) allocate
/// - soap_new_ns1__relation(soap*, int num) allocate array
/// - soap_new_req_ns1__relation(soap*, ...) allocate, set required members
/// - soap_new_set_ns1__relation(soap*, ...) allocate, set all public members
/// - int soap_read_ns1__relation(soap*, ns1__relation*) deserialize from a stream
/// - int soap_write_ns1__relation(soap, ns1__relation*) serialize to a stream
class ns1__relation
{ public:
/// Vector of xsd__anyURI with length 1..unbounded
    std::vector<xsd__anyURI            > node_id                        1;
/// Vector of xsd__anyURI with length 1..unbounded
    std::vector<xsd__anyURI            > service_id                     1;
/// Attribute relation-id of type xs:int.
   @int                                  relation_id                    1;	///< Required attribute.
/// Attribute anonymous-method of type xs:string.
   @std::string                          anonymous_method               1;	///< Required attribute.
/// Attribute privacy-lvl of type xs:string.
   @std::string                          privacy_lvl                    1;	///< Required attribute.
};

/// "urn:rm":body is a complexType.
/// class ns1__body operations:
/// - soap_new_ns1__body(soap*) allocate
/// - soap_new_ns1__body(soap*, int num) allocate array
/// - soap_new_req_ns1__body(soap*, ...) allocate, set required members
/// - soap_new_set_ns1__body(soap*, ...) allocate, set all public members
/// - int soap_read_ns1__body(soap*, ns1__body*) deserialize from a stream
/// - int soap_write_ns1__body(soap, ns1__body*) serialize to a stream
class ns1__body
{ public:
/// Vector of ns1__relation* with length 0..unbounded
    std::vector<ns1__relation*         > relation                       0;	///< Nillable pointer.
};

/// "urn:rm":header is a complexType.
/// class ns1__header operations:
/// - soap_new_ns1__header(soap*) allocate
/// - soap_new_ns1__header(soap*, int num) allocate array
/// - soap_new_req_ns1__header(soap*, ...) allocate, set required members
/// - soap_new_set_ns1__header(soap*, ...) allocate, set all public members
/// - int soap_read_ns1__header(soap*, ns1__header*) deserialize from a stream
/// - int soap_write_ns1__header(soap, ns1__header*) serialize to a stream
class ns1__header
{ public:
/// Attribute massage of type xs:string.
   @std::string                          massage                        1;	///< Required attribute.
};

/// "urn:rm":transport is a complexType.
/// class ns1__transport operations:
/// - soap_new_ns1__transport(soap*) allocate
/// - soap_new_ns1__transport(soap*, int num) allocate array
/// - soap_new_req_ns1__transport(soap*, ...) allocate, set required members
/// - soap_new_set_ns1__transport(soap*, ...) allocate, set all public members
/// - int soap_read_ns1__transport(soap*, ns1__transport*) deserialize from a stream
/// - int soap_write_ns1__transport(soap, ns1__transport*) serialize to a stream
class ns1__transport
{ public:
/// Element header of type "urn:rm":header.
    ns1__header*                         header                         1;	///< Nillable pointer.
/// Element body of type "urn:rm":body.
    ns1__body*                           body                           1;	///< Nillable pointer.
};

/// Top-level root element "urn:rm":dataRQ

/// "urn:rm":dataRQ is a complexType.
/// class _ns1__dataRQ operations:
/// - soap_new__ns1__dataRQ(soap*) allocate
/// - soap_new__ns1__dataRQ(soap*, int num) allocate array
/// - soap_new_req__ns1__dataRQ(soap*, ...) allocate, set required members
/// - soap_new_set__ns1__dataRQ(soap*, ...) allocate, set all public members
/// - int soap_read__ns1__dataRQ(soap*, _ns1__dataRQ*) deserialize from a stream
/// - int soap_write__ns1__dataRQ(soap, _ns1__dataRQ*) serialize to a stream
class _ns1__dataRQ
{ public:
/// Element transport of type "urn:rm":transport.
    ns1__transport*                      transport                      1;	///< Nillable pointer.
};


/// Top-level root element "urn:rm":dataRS

/// "urn:rm":dataRS is a complexType.
/// class _ns1__dataRS operations:
/// - soap_new__ns1__dataRS(soap*) allocate
/// - soap_new__ns1__dataRS(soap*, int num) allocate array
/// - soap_new_req__ns1__dataRS(soap*, ...) allocate, set required members
/// - soap_new_set__ns1__dataRS(soap*, ...) allocate, set all public members
/// - int soap_read__ns1__dataRS(soap*, _ns1__dataRS*) deserialize from a stream
/// - int soap_write__ns1__dataRS(soap, _ns1__dataRS*) serialize to a stream
class _ns1__dataRS
{ public:
/// Element transport of type "urn:rm":transport.
    ns1__transport*                      transport                      1;	///< Nillable pointer.
};
//gsoap ns1  service name:	RManager 
//gsoap ns1  service type:	RManagerPortType 
//gsoap ns1  service port:	http://10.0.0.2/cgi-bin/server.cgi 
//gsoap ns1  service namespace:	urn:rm 
//gsoap ns1  service transport:	http://schemas.xmlsoap.org/soap/http 

//gsoap ns1  service method-protocol:	data SOAP
//gsoap ns1  service method-style:	data rpc
//gsoap ns1  service method-action:	data ""
//gsoap ns1  service method-output-action:	data Response
int ns1__data(
    _ns1__dataRQ*                       req,	///< Input parameter
    _ns1__dataRS                        &res	///< Output parameter
);
