#pragma one

namespace tarantool {
namespace protocol {

namespace consts {

constexpr std::size_t greeting_server_version_len	= 64;
constexpr std::size_t greeting_server_salt_len		= 44;
constexpr std::size_t greeting_server_rest_len		= 20;


} // consts

// copy-pasted from https://github.com/tarantool/tarantool/blob/1.9/src/box/iproto_constants.h
enum class iproto_keys
{
	request_type = 0x00,
	sync = 0x01,

	/* replication keys (header) */
	replica_id = 0x02,
	lsn = 0x03,
	timestamp = 0x04,
	schema_version = 0x05,
	server_version = 0x06,
	server_is_ro = 0x07,

	/* leave a gap for other keys in the header. */
	space_id = 0x10,
	index_id = 0x11,
	limit = 0x12,
	offset = 0x13,
	iterator = 0x14,
	index_base = 0x15,

	/* leave a gap between integer values and other keys */
	key = 0x20,
	tuple = 0x21,
	function_name = 0x22,
	user_name = 0x23,

	/* replication keys (body) */
	instance_uuid = 0x24,
	cluster_uuid = 0x25,
	vclock = 0x26,
	expr = 0x27, /* eval */
	ops = 0x28, /* upsert but not update ops, because of legacy */

	/* leave a gap between request keys and response keys */
	data = 0x30,
	error = 0x31
};

// copy-pasted from https://github.com/tarantool/tarantool/blob/1.9/src/box/iproto_constants.h
enum class iproto_type
{
	/** Acknowledgement that request or command is successful */
	ok = 0,
	/** SELECT request */
	select = 1,
	/** INSERT request */
	insert = 2,
	/** REPLACE request */
	replace = 3,
	/** UPDATE request */
	update = 4,
	/** DELETE request */
	erase = 5, // delete -> erase
	/** CALL request - wraps result into [tuple, tuple, ...] format */
	call_16 = 6,
	/** AUTH request */
	auth = 7,
	/** EVAL request */
	eval = 8,
	/** UPSERT request */
	upsert = 9,
	/** CALL request - returns arbitrary MessagePack */
	call = 10,
	/* 11 is reserved for SQL */
	/** No operation. Treated as DML, used to bump LSN. */
	nop = 12,
	/** The maximum typecode used for box.stat() */
	type_stat_max,

	/** PING request */
	ping = 64,
	/** Replication JOIN command */
	join = 65,
	/** Replication SUBSCRIBE command */
	subscribe = 66,
	/** Vote request command for master election */
	request_vote = 67,

	/** Vinyl run info stored in .index file */
	vy_index_run_info = 100,
	/** Vinyl page info stored in .index file */
	vy_index_page_info = 101,
	/** Vinyl row index stored in .run file */
	vy_run_row_index = 102,

	/**
	 * Error codes = (TYPE_ERROR | ER_XXX from errcode.h)
	 */
	type_error = 1 << 15
};

} // protocol
} // tarantool
