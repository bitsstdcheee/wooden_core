// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: proto/TagDied.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_proto_2fTagDied_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_proto_2fTagDied_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION < 4023000
#error "This file was generated by a newer version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please update"
#error "your headers."
#endif  // PROTOBUF_VERSION

#if 4023004 < PROTOBUF_MIN_PROTOC_VERSION
#error "This file was generated by an older version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please"
#error "regenerate this file with a newer version of protoc."
#endif  // PROTOBUF_MIN_PROTOC_VERSION
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/message.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_proto_2fTagDied_2eproto

PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_proto_2fTagDied_2eproto {
    static const ::uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable
    descriptor_table_proto_2fTagDied_2eproto;
namespace proto {
class PTagDied;
struct PTagDiedDefaultTypeInternal;
extern PTagDiedDefaultTypeInternal _PTagDied_default_instance_;
}  // namespace proto
PROTOBUF_NAMESPACE_OPEN
template <>
::proto::PTagDied* Arena::CreateMaybeMessage<::proto::PTagDied>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

namespace proto {

// ===================================================================

// -------------------------------------------------------------------

class PTagDied final : public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:proto.PTagDied)
                                                                */
{
   public:
    inline PTagDied() : PTagDied(nullptr) {}
    ~PTagDied() override;
    template <typename = void>
    explicit PROTOBUF_CONSTEXPR PTagDied(
        ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

    PTagDied(const PTagDied& from);
    PTagDied(PTagDied&& from) noexcept : PTagDied() {
        *this = ::std::move(from);
    }

    inline PTagDied& operator=(const PTagDied& from) {
        CopyFrom(from);
        return *this;
    }
    inline PTagDied& operator=(PTagDied&& from) noexcept {
        if (this == &from) return *this;
        if (GetOwningArena() == from.GetOwningArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
            && GetOwningArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
        ) {
            InternalSwap(&from);
        } else {
            CopyFrom(from);
        }
        return *this;
    }

    inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields()
        const {
        return _internal_metadata_
            .unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(
                ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
    }
    inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
        return _internal_metadata_
            .mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
    }

    static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
        return GetDescriptor();
    }
    static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
        return default_instance().GetMetadata().descriptor;
    }
    static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
        return default_instance().GetMetadata().reflection;
    }
    static const PTagDied& default_instance() {
        return *internal_default_instance();
    }
    static inline const PTagDied* internal_default_instance() {
        return reinterpret_cast<const PTagDied*>(&_PTagDied_default_instance_);
    }
    static constexpr int kIndexInFileMessages = 0;

    friend void swap(PTagDied& a, PTagDied& b) { a.Swap(&b); }
    inline void Swap(PTagDied* other) {
        if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
        if (GetOwningArena() != nullptr &&
            GetOwningArena() == other->GetOwningArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
        if (GetOwningArena() == other->GetOwningArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
            InternalSwap(other);
        } else {
            ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
        }
    }
    void UnsafeArenaSwap(PTagDied* other) {
        if (other == this) return;
        ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
        InternalSwap(other);
    }

    // implements Message ----------------------------------------------

    PTagDied* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
        return CreateMaybeMessage<PTagDied>(arena);
    }
    using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
    void CopyFrom(const PTagDied& from);
    using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
    void MergeFrom(const PTagDied& from) { PTagDied::MergeImpl(*this, from); }

   private:
    static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg,
                          const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);

   public:
    PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
    bool IsInitialized() const final;

    ::size_t ByteSizeLong() const final;
    const char* _InternalParse(
        const char* ptr,
        ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
    ::uint8_t* _InternalSerialize(
        ::uint8_t* target,
        ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
    int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

   private:
    void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
    void SharedDtor();
    void SetCachedSize(int size) const final;
    void InternalSwap(PTagDied* other);

   private:
    friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
    static ::absl::string_view FullMessageName() { return "proto.PTagDied"; }

   protected:
    explicit PTagDied(::PROTOBUF_NAMESPACE_ID::Arena* arena);

   public:
    static const ClassData _class_data_;
    const ::PROTOBUF_NAMESPACE_ID::Message::ClassData* GetClassData()
        const final;

    ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

    // nested types ----------------------------------------------------

    // accessors -------------------------------------------------------

    enum : int {
        kIdFieldNumber = 1,
        kTagFieldNumber = 2,
    };
    // required int32 id = 1;
    bool has_id() const;
    void clear_id();
    ::int32_t id() const;
    void set_id(::int32_t value);

   private:
    ::int32_t _internal_id() const;
    void _internal_set_id(::int32_t value);

   public:
    // required bool tag = 2;
    bool has_tag() const;
    void clear_tag();
    bool tag() const;
    void set_tag(bool value);

   private:
    bool _internal_tag() const;
    void _internal_set_tag(bool value);

   public:
    // @@protoc_insertion_point(class_scope:proto.PTagDied)
   private:
    class _Internal;

    // helper for ByteSizeLong()
    ::size_t RequiredFieldsByteSizeFallback() const;

    template <typename T>
    friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
    typedef void InternalArenaConstructable_;
    typedef void DestructorSkippable_;
    struct Impl_ {
        ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
        mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
        ::int32_t id_;
        bool tag_;
    };
    union {
        Impl_ _impl_;
    };
    friend struct ::TableStruct_proto_2fTagDied_2eproto;
};

// ===================================================================

// ===================================================================

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// PTagDied

// required int32 id = 1;
inline bool PTagDied::has_id() const {
    bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
    return value;
}
inline void PTagDied::clear_id() {
    _impl_.id_ = 0;
    _impl_._has_bits_[0] &= ~0x00000001u;
}
inline ::int32_t PTagDied::id() const {
    // @@protoc_insertion_point(field_get:proto.PTagDied.id)
    return _internal_id();
}
inline void PTagDied::set_id(::int32_t value) {
    _internal_set_id(value);
    // @@protoc_insertion_point(field_set:proto.PTagDied.id)
}
inline ::int32_t PTagDied::_internal_id() const { return _impl_.id_; }
inline void PTagDied::_internal_set_id(::int32_t value) {
    _impl_._has_bits_[0] |= 0x00000001u;
    _impl_.id_ = value;
}

// required bool tag = 2;
inline bool PTagDied::has_tag() const {
    bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
    return value;
}
inline void PTagDied::clear_tag() {
    _impl_.tag_ = false;
    _impl_._has_bits_[0] &= ~0x00000002u;
}
inline bool PTagDied::tag() const {
    // @@protoc_insertion_point(field_get:proto.PTagDied.tag)
    return _internal_tag();
}
inline void PTagDied::set_tag(bool value) {
    _internal_set_tag(value);
    // @@protoc_insertion_point(field_set:proto.PTagDied.tag)
}
inline bool PTagDied::_internal_tag() const { return _impl_.tag_; }
inline void PTagDied::_internal_set_tag(bool value) {
    _impl_._has_bits_[0] |= 0x00000002u;
    _impl_.tag_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto

// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_proto_2fTagDied_2eproto_2epb_2eh
