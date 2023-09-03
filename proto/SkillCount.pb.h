// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: proto/SkillCount.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_proto_2fSkillCount_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_proto_2fSkillCount_2eproto_2epb_2eh

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

#define PROTOBUF_INTERNAL_EXPORT_proto_2fSkillCount_2eproto

PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_proto_2fSkillCount_2eproto {
    static const ::uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable
    descriptor_table_proto_2fSkillCount_2eproto;
namespace proto {
class PSkillCount;
struct PSkillCountDefaultTypeInternal;
extern PSkillCountDefaultTypeInternal _PSkillCount_default_instance_;
class PSkillCountSingle;
struct PSkillCountSingleDefaultTypeInternal;
extern PSkillCountSingleDefaultTypeInternal
    _PSkillCountSingle_default_instance_;
}  // namespace proto
PROTOBUF_NAMESPACE_OPEN
template <>
::proto::PSkillCount* Arena::CreateMaybeMessage<::proto::PSkillCount>(Arena*);
template <>
::proto::PSkillCountSingle*
Arena::CreateMaybeMessage<::proto::PSkillCountSingle>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

namespace proto {

// ===================================================================

// -------------------------------------------------------------------

class PSkillCountSingle final : public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:proto.PSkillCountSingle)
                                                                         */
{
   public:
    inline PSkillCountSingle() : PSkillCountSingle(nullptr) {}
    ~PSkillCountSingle() override;
    template <typename = void>
    explicit PROTOBUF_CONSTEXPR PSkillCountSingle(
        ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

    PSkillCountSingle(const PSkillCountSingle& from);
    PSkillCountSingle(PSkillCountSingle&& from) noexcept : PSkillCountSingle() {
        *this = ::std::move(from);
    }

    inline PSkillCountSingle& operator=(const PSkillCountSingle& from) {
        CopyFrom(from);
        return *this;
    }
    inline PSkillCountSingle& operator=(PSkillCountSingle&& from) noexcept {
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
    static const PSkillCountSingle& default_instance() {
        return *internal_default_instance();
    }
    static inline const PSkillCountSingle* internal_default_instance() {
        return reinterpret_cast<const PSkillCountSingle*>(
            &_PSkillCountSingle_default_instance_);
    }
    static constexpr int kIndexInFileMessages = 0;

    friend void swap(PSkillCountSingle& a, PSkillCountSingle& b) { a.Swap(&b); }
    inline void Swap(PSkillCountSingle* other) {
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
    void UnsafeArenaSwap(PSkillCountSingle* other) {
        if (other == this) return;
        ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
        InternalSwap(other);
    }

    // implements Message ----------------------------------------------

    PSkillCountSingle* New(
        ::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
        return CreateMaybeMessage<PSkillCountSingle>(arena);
    }
    using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
    void CopyFrom(const PSkillCountSingle& from);
    using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
    void MergeFrom(const PSkillCountSingle& from) {
        PSkillCountSingle::MergeImpl(*this, from);
    }

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
    void InternalSwap(PSkillCountSingle* other);

   private:
    friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
    static ::absl::string_view FullMessageName() {
        return "proto.PSkillCountSingle";
    }

   protected:
    explicit PSkillCountSingle(::PROTOBUF_NAMESPACE_ID::Arena* arena);

   public:
    static const ClassData _class_data_;
    const ::PROTOBUF_NAMESPACE_ID::Message::ClassData* GetClassData()
        const final;

    ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

    // nested types ----------------------------------------------------

    // accessors -------------------------------------------------------

    enum : int {
        kSklFieldNumber = 1,
        kCountFieldNumber = 2,
    };
    // required int32 skl = 1;
    bool has_skl() const;
    void clear_skl();
    ::int32_t skl() const;
    void set_skl(::int32_t value);

   private:
    ::int32_t _internal_skl() const;
    void _internal_set_skl(::int32_t value);

   public:
    // required int32 count = 2;
    bool has_count() const;
    void clear_count();
    ::int32_t count() const;
    void set_count(::int32_t value);

   private:
    ::int32_t _internal_count() const;
    void _internal_set_count(::int32_t value);

   public:
    // @@protoc_insertion_point(class_scope:proto.PSkillCountSingle)
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
        ::int32_t skl_;
        ::int32_t count_;
    };
    union {
        Impl_ _impl_;
    };
    friend struct ::TableStruct_proto_2fSkillCount_2eproto;
};  // -------------------------------------------------------------------

class PSkillCount final : public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:proto.PSkillCount)
                                                                   */
{
   public:
    inline PSkillCount() : PSkillCount(nullptr) {}
    ~PSkillCount() override;
    template <typename = void>
    explicit PROTOBUF_CONSTEXPR PSkillCount(
        ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

    PSkillCount(const PSkillCount& from);
    PSkillCount(PSkillCount&& from) noexcept : PSkillCount() {
        *this = ::std::move(from);
    }

    inline PSkillCount& operator=(const PSkillCount& from) {
        CopyFrom(from);
        return *this;
    }
    inline PSkillCount& operator=(PSkillCount&& from) noexcept {
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
    static const PSkillCount& default_instance() {
        return *internal_default_instance();
    }
    static inline const PSkillCount* internal_default_instance() {
        return reinterpret_cast<const PSkillCount*>(
            &_PSkillCount_default_instance_);
    }
    static constexpr int kIndexInFileMessages = 1;

    friend void swap(PSkillCount& a, PSkillCount& b) { a.Swap(&b); }
    inline void Swap(PSkillCount* other) {
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
    void UnsafeArenaSwap(PSkillCount* other) {
        if (other == this) return;
        ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
        InternalSwap(other);
    }

    // implements Message ----------------------------------------------

    PSkillCount* New(
        ::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
        return CreateMaybeMessage<PSkillCount>(arena);
    }
    using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
    void CopyFrom(const PSkillCount& from);
    using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
    void MergeFrom(const PSkillCount& from) {
        PSkillCount::MergeImpl(*this, from);
    }

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
    void InternalSwap(PSkillCount* other);

   private:
    friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
    static ::absl::string_view FullMessageName() { return "proto.PSkillCount"; }

   protected:
    explicit PSkillCount(::PROTOBUF_NAMESPACE_ID::Arena* arena);

   public:
    static const ClassData _class_data_;
    const ::PROTOBUF_NAMESPACE_ID::Message::ClassData* GetClassData()
        const final;

    ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

    // nested types ----------------------------------------------------

    // accessors -------------------------------------------------------

    enum : int {
        kListFieldNumber = 2,
        kIdFieldNumber = 1,
    };
    // repeated .proto.PSkillCountSingle list = 2;
    int list_size() const;

   private:
    int _internal_list_size() const;

   public:
    void clear_list();
    ::proto::PSkillCountSingle* mutable_list(int index);
    ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::proto::PSkillCountSingle>*
    mutable_list();

   private:
    const ::proto::PSkillCountSingle& _internal_list(int index) const;
    ::proto::PSkillCountSingle* _internal_add_list();
    const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::proto::PSkillCountSingle>&
    _internal_list() const;
    ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::proto::PSkillCountSingle>*
    _internal_mutable_list();

   public:
    const ::proto::PSkillCountSingle& list(int index) const;
    ::proto::PSkillCountSingle* add_list();
    const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::proto::PSkillCountSingle>&
    list() const;
    // required int32 id = 1;
    bool has_id() const;
    void clear_id();
    ::int32_t id() const;
    void set_id(::int32_t value);

   private:
    ::int32_t _internal_id() const;
    void _internal_set_id(::int32_t value);

   public:
    // @@protoc_insertion_point(class_scope:proto.PSkillCount)
   private:
    class _Internal;

    template <typename T>
    friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
    typedef void InternalArenaConstructable_;
    typedef void DestructorSkippable_;
    struct Impl_ {
        ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
        mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
        ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::proto::PSkillCountSingle>
            list_;
        ::int32_t id_;
    };
    union {
        Impl_ _impl_;
    };
    friend struct ::TableStruct_proto_2fSkillCount_2eproto;
};

// ===================================================================

// ===================================================================

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// PSkillCountSingle

// required int32 skl = 1;
inline bool PSkillCountSingle::has_skl() const {
    bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
    return value;
}
inline void PSkillCountSingle::clear_skl() {
    _impl_.skl_ = 0;
    _impl_._has_bits_[0] &= ~0x00000001u;
}
inline ::int32_t PSkillCountSingle::skl() const {
    // @@protoc_insertion_point(field_get:proto.PSkillCountSingle.skl)
    return _internal_skl();
}
inline void PSkillCountSingle::set_skl(::int32_t value) {
    _internal_set_skl(value);
    // @@protoc_insertion_point(field_set:proto.PSkillCountSingle.skl)
}
inline ::int32_t PSkillCountSingle::_internal_skl() const {
    return _impl_.skl_;
}
inline void PSkillCountSingle::_internal_set_skl(::int32_t value) {
    _impl_._has_bits_[0] |= 0x00000001u;
    _impl_.skl_ = value;
}

// required int32 count = 2;
inline bool PSkillCountSingle::has_count() const {
    bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
    return value;
}
inline void PSkillCountSingle::clear_count() {
    _impl_.count_ = 0;
    _impl_._has_bits_[0] &= ~0x00000002u;
}
inline ::int32_t PSkillCountSingle::count() const {
    // @@protoc_insertion_point(field_get:proto.PSkillCountSingle.count)
    return _internal_count();
}
inline void PSkillCountSingle::set_count(::int32_t value) {
    _internal_set_count(value);
    // @@protoc_insertion_point(field_set:proto.PSkillCountSingle.count)
}
inline ::int32_t PSkillCountSingle::_internal_count() const {
    return _impl_.count_;
}
inline void PSkillCountSingle::_internal_set_count(::int32_t value) {
    _impl_._has_bits_[0] |= 0x00000002u;
    _impl_.count_ = value;
}

// -------------------------------------------------------------------

// PSkillCount

// required int32 id = 1;
inline bool PSkillCount::has_id() const {
    bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
    return value;
}
inline void PSkillCount::clear_id() {
    _impl_.id_ = 0;
    _impl_._has_bits_[0] &= ~0x00000001u;
}
inline ::int32_t PSkillCount::id() const {
    // @@protoc_insertion_point(field_get:proto.PSkillCount.id)
    return _internal_id();
}
inline void PSkillCount::set_id(::int32_t value) {
    _internal_set_id(value);
    // @@protoc_insertion_point(field_set:proto.PSkillCount.id)
}
inline ::int32_t PSkillCount::_internal_id() const { return _impl_.id_; }
inline void PSkillCount::_internal_set_id(::int32_t value) {
    _impl_._has_bits_[0] |= 0x00000001u;
    _impl_.id_ = value;
}

// repeated .proto.PSkillCountSingle list = 2;
inline int PSkillCount::_internal_list_size() const {
    return _impl_.list_.size();
}
inline int PSkillCount::list_size() const { return _internal_list_size(); }
inline void PSkillCount::clear_list() { _internal_mutable_list()->Clear(); }
inline ::proto::PSkillCountSingle* PSkillCount::mutable_list(int index) {
    // @@protoc_insertion_point(field_mutable:proto.PSkillCount.list)
    return _internal_mutable_list()->Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::proto::PSkillCountSingle>*
PSkillCount::mutable_list() {
    // @@protoc_insertion_point(field_mutable_list:proto.PSkillCount.list)
    return _internal_mutable_list();
}
inline const ::proto::PSkillCountSingle& PSkillCount::_internal_list(
    int index) const {
    return _internal_list().Get(index);
}
inline const ::proto::PSkillCountSingle& PSkillCount::list(int index) const {
    // @@protoc_insertion_point(field_get:proto.PSkillCount.list)
    return _internal_list(index);
}
inline ::proto::PSkillCountSingle* PSkillCount::_internal_add_list() {
    return _internal_mutable_list()->Add();
}
inline ::proto::PSkillCountSingle* PSkillCount::add_list() {
    ::proto::PSkillCountSingle* _add = _internal_add_list();
    // @@protoc_insertion_point(field_add:proto.PSkillCount.list)
    return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<
    ::proto::PSkillCountSingle>&
PSkillCount::list() const {
    // @@protoc_insertion_point(field_list:proto.PSkillCount.list)
    return _internal_list();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<
    ::proto::PSkillCountSingle>&
PSkillCount::_internal_list() const {
    return _impl_.list_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::proto::PSkillCountSingle>*
PSkillCount::_internal_mutable_list() {
    return &_impl_.list_;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto

// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_proto_2fSkillCount_2eproto_2epb_2eh
