//  Copyright (c)      2014 Thomas Heller
//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime.hpp>
#include <hpx/runtime/parcelset/parcelhandler.hpp>
#include <hpx/runtime/parcelset/locality.hpp>

#include <boost/foreach.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace parcelset
{
    void locality::save(util::portable_binary_oarchive & ar, const unsigned int version) const
    {
        std::string t = type();
        ar << t;
        if(t.empty()) return;
        impl_->save(ar);
    }

    void locality::load(util::portable_binary_iarchive & ar, const unsigned int version)
    {
        std::string t;
        ar >> t;
        if(t.empty()) return;
        HPX_ASSERT(get_runtime_ptr());
        impl_ = std::move(get_runtime().get_parcel_handler().create_locality(t).impl_);
        impl_->load(ar);
        HPX_ASSERT(impl_->valid());
    }

    std::ostream& operator<< (std::ostream& os, endpoints_type const& endpoints)
    {
        boost::io::ios_flags_saver ifs(os);
        os << "[ ";
        BOOST_FOREACH(endpoints_type::value_type const & loc, endpoints)
        {
            os << "(" << loc.first << ":" << loc.second << ") ";
        }
        os << "]";

        return os;
    }
}}
