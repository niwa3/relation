// STL vector containers (use option -s to remove STL dependency)
#import "stlvector.h"

#define SOAP_NAMESPACE_OF_ns1	"urn:rm"
//gsoap ns1   schema namespace:	urn:rm
//gsoap ns1   schema form:	qualified

typedef std::string xsd__anyURI;

//  Forward declaration of class ns1__relation.
class ns1__relation;

//  Forward declaration of class ns1__body.
class ns1__body;

//  Forward declaration of class ns1__header.
class ns1__header;

//  Forward declaration of class ns1__transport.
class ns1__transport;

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
/// Element node-id of type xs:anyURI.
    xsd__anyURI                          node_id                        1;	///< Required element.
/// Element service-id of type xs:anyURI.
    xsd__anyURI                          service_id                     1;	///< Required element.
/// Element relation-id of type xs:int.
    int                                  relation_id                    1;	///< Required element.
/// Element anonymous-method of type xs:string.
    std::string                          anonymous_method               1;	///< Required element.
/// Element privacy-lvl of type xs:int.
    int                                  privacy_lvl                    1;	///< Required element.
/// Element interval of type xs:int.
    int                                  interval                       1;	///< Required element.
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
/// Vector of ns1__relation* with length 1..unbounded
    std::vector<ns1__relation         > relation                        0;	///< Nillable pointer.
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
    ns1__header                         header                         1;	///< Nillable pointer.
/// Element body of type "urn:rm":body.
    ns1__body                           body                           1;	///< Nillable pointer.
};

/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Elements                                              *
 *   urn:rm                                                                   *
 *                                                                            *
\******************************************************************************/


/// Top-level root element "urn:rm":req of type "urn:rm":transport.
/// Note: use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// Top-level root element "urn:rm":res of type "urn:rm":transport.
/// Note: use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Attributes                                            *
 *   urn:rm                                                                   *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Services                                                                   *
 *                                                                            *
\******************************************************************************/


//gsoap ns1  service name:	RManager 
//gsoap ns1  service type:	RManagerPortType 
//gsoap ns1  service port:	http://10.0.0.2/cgi-bin/server.cgi 
//gsoap ns1  service namespace:	urn:rm 
//gsoap ns1  service transport:	http://schemas.xmlsoap.org/soap/http 


//gsoap ns1  service method-protocol:	register SOAP
//gsoap ns1  service method-style:	register rpc
//gsoap ns1  service method-encoding:	register http://schemas.xmlsoap.org/soap/encoding/
//gsoap ns1  service method-action:	register ""
//gsoap ns1  service method-output-action:	register Response
int ns1__register(
    ns1__transport*                     req,	///< Input parameter
    ns1__transport                      &res	///< Output parameter
);

//gsoap ns1  service method-protocol:	change SOAP
//gsoap ns1  service method-style:	change rpc
//gsoap ns1  service method-encoding:	change http://schemas.xmlsoap.org/soap/encoding/
//gsoap ns1  service method-action:	change ""
//gsoap ns1  service method-output-action:	change Response
int ns1__change(
    ns1__transport*                     req,	///< Input parameter
    ns1__transport                      &res	///< Output parameter
);

//gsoap ns1  service method-protocol:	delete SOAP
//gsoap ns1  service method-style:	delete rpc
//gsoap ns1  service method-encoding:	delete http://schemas.xmlsoap.org/soap/encoding/
//gsoap ns1  service method-action:	delete ""
//gsoap ns1  service method-output-action:	delete Response
int ns1__delete(
    ns1__transport*                     req,	///< Input parameter
    ns1__transport                      &res	///< Output parameter
);

/* End of RManager.h */
